#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned short usecs; int* frame_usecs; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_6__ {unsigned short* frame_usecs; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */
 unsigned short* max_uframe_usecs ; 

__attribute__((used)) static int find_multi_uframe(dwc_otg_hcd_t * _hcd, dwc_otg_qh_t * _qh)
{
	int i;
	int j;
	unsigned short utime;
	int t_left;
	int ret;
	int done;
	unsigned short xtime;

	ret = -1;
	utime = _qh->usecs;
	t_left = utime;
	i = 0;
	done = 0;
loop:
	while (done == 0) {
		if(_hcd->frame_usecs[i] <= 0) {
			i++;
			if (i == 8) {
				done = 1;
				ret = -1;
			}
			goto loop;
		}

		/*
		 * we need n consecutive slots
		 * so use j as a start slot j plus j+1 must be enough time (for now)
		 */
		xtime= _hcd->frame_usecs[i];
		for (j = i+1 ; j < 8 ; j++ ) {
                       /*
                        * if we add this frame remaining time to xtime we may
                        * be OK, if not we need to test j for a complete frame
                        */
                       if ((xtime+_hcd->frame_usecs[j]) < utime) {
                               if (_hcd->frame_usecs[j] < max_uframe_usecs[j]) {
                                       j = 8;
                                       ret = -1;
                                       continue;
                               }
                       }
                       if (xtime >= utime) {
                               ret = i;
                               j = 8;  /* stop loop with a good value ret */
                               continue;
                       }
                       /* add the frame time to x time */
                       xtime += _hcd->frame_usecs[j];
		       /* we must have a fully available next frame or break */
		       if ((xtime < utime)
				       && (_hcd->frame_usecs[j] == max_uframe_usecs[j])) {
			       ret = -1;
			       j = 8;  /* stop loop with a bad value ret */
			       continue;
		       }
		}
		if (ret >= 0) {
			t_left = utime;
			for (j = i; (t_left>0) && (j < 8); j++ ) {
				t_left -= _hcd->frame_usecs[j];
				if ( t_left <= 0 ) {
					_qh->frame_usecs[j] += _hcd->frame_usecs[j] + t_left;
					_hcd->frame_usecs[j]= -t_left;
					ret = i;
					done = 1;
				} else {
					_qh->frame_usecs[j] += _hcd->frame_usecs[j];
					_hcd->frame_usecs[j] = 0;
				}
			}
		} else {
			i++;
			if (i == 8) {
				done = 1;
				ret = -1;
			}
		}
	}
	return ret;
}