#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u16 ;
struct b43_wldev {int dummy; } ;
struct b43_rfatt {void* att; } ;
struct b43_lo_calib {int /*<<< orphan*/  ctl; } ;
struct b43_bbatt {void* att; } ;
typedef  int /*<<< orphan*/  rf ;
typedef  int /*<<< orphan*/  bb ;

/* Variables and functions */
 struct b43_lo_calib* b43_get_calib_lo_settings (struct b43_wldev*,struct b43_rfatt*,struct b43_rfatt*) ; 
 int /*<<< orphan*/  b43_lo_fixup_rfatt (struct b43_rfatt*) ; 
 int /*<<< orphan*/  b43_lo_write (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct b43_rfatt*,int /*<<< orphan*/ ,int) ; 

void b43_lo_g_adjust_to(struct b43_wldev *dev,
			u16 rfatt, u16 bbatt, u16 tx_control)
{
	struct b43_rfatt rf;
	struct b43_bbatt bb;
	struct b43_lo_calib *cal;

	memset(&rf, 0, sizeof(rf));
	memset(&bb, 0, sizeof(bb));
	rf.att = rfatt;
	bb.att = bbatt;
	b43_lo_fixup_rfatt(&rf);
	cal = b43_get_calib_lo_settings(dev, &bb, &rf);
	if (!cal)
		return;
	b43_lo_write(dev, &cal->ctl);
}