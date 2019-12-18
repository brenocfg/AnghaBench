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
struct rfcomm_dlc {int /*<<< orphan*/  flags; int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  cfc; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_MSC_PENDING ; 
 int /*<<< orphan*/  RFCOMM_V24_FC ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __rfcomm_dlc_throttle(struct rfcomm_dlc *d)
{
	BT_DBG("dlc %p state %ld", d, d->state);

	if (!d->cfc) {
		d->v24_sig |= RFCOMM_V24_FC;
		set_bit(RFCOMM_MSC_PENDING, &d->flags);
	}
	rfcomm_schedule();
}