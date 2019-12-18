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
typedef  int /*<<< orphan*/  u8 ;
struct rfcomm_dlc {int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rfcomm_dlc_get_modem_status(struct rfcomm_dlc *d, u8 *v24_sig)
{
	BT_DBG("dlc %p state %ld v24_sig 0x%x",
			d, d->state, d->v24_sig);

	*v24_sig = d->v24_sig;
	return 0;
}