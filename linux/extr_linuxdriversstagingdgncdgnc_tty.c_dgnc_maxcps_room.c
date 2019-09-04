#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long digi_maxcps; unsigned long digi_bufsize; } ;
struct channel_t {unsigned long ch_cpstime; TYPE_1__ ch_digi; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long jiffies ; 
 int min (int,int) ; 

__attribute__((used)) static int dgnc_maxcps_room(struct channel_t *ch, int bytes_available)
{
	int rc = bytes_available;

	if (ch->ch_digi.digi_maxcps > 0 && ch->ch_digi.digi_bufsize > 0) {
		int cps_limit = 0;
		unsigned long current_time = jiffies;
		unsigned long buffer_time = current_time +
			(HZ * ch->ch_digi.digi_bufsize) /
			ch->ch_digi.digi_maxcps;

		if (ch->ch_cpstime < current_time) {
			/* buffer is empty */
			ch->ch_cpstime = current_time;	/* reset ch_cpstime */
			cps_limit = ch->ch_digi.digi_bufsize;
		} else if (ch->ch_cpstime < buffer_time) {
			/* still room in the buffer */
			cps_limit = ((buffer_time - ch->ch_cpstime) *
					ch->ch_digi.digi_maxcps) / HZ;
		} else {
			/* no room in the buffer */
			cps_limit = 0;
		}

		rc = min(cps_limit, bytes_available);
	}

	return rc;
}