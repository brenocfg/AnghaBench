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
struct TYPE_5__ {unsigned short usecs; unsigned short* frame_usecs; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_6__ {unsigned short* frame_usecs; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */

__attribute__((used)) static int find_single_uframe(dwc_otg_hcd_t * _hcd, dwc_otg_qh_t * _qh)
{
	int i;
	unsigned short utime;
	int t_left;
	int ret;
	int done;

	ret = -1;
	utime = _qh->usecs;
	t_left = utime;
	i = 0;
	done = 0;
	while (done == 0) {
		/* At the start _hcd->frame_usecs[i] = max_uframe_usecs[i]; */
		if (utime <= _hcd->frame_usecs[i]) {
			_hcd->frame_usecs[i] -= utime;
			_qh->frame_usecs[i] += utime;
			t_left -= utime;
			ret = i;
			done = 1;
			return ret;
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