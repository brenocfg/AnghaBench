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
struct tpacpi_rfk {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_status ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TPACPI_DBG_RFKILL ; 
 int /*<<< orphan*/  TPACPI_RFK_RADIO_OFF ; 
 int /*<<< orphan*/  TPACPI_RFK_RADIO_ON ; 
 int /*<<< orphan*/  dbg_printk (int /*<<< orphan*/ ,char*,char*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpacpi_rfk_update_swstate (struct tpacpi_rfk*) ; 

__attribute__((used)) static int tpacpi_rfk_hook_set_block(void *data, bool blocked)
{
	struct tpacpi_rfk *tp_rfk = data;
	int res;

	dbg_printk(TPACPI_DBG_RFKILL,
		   "request to change radio state to %s\n",
		   blocked ? "blocked" : "unblocked");

	/* try to set radio state */
	res = (tp_rfk->ops->set_status)(blocked ?
				TPACPI_RFK_RADIO_OFF : TPACPI_RFK_RADIO_ON);

	/* and update the rfkill core with whatever the FW really did */
	tpacpi_rfk_update_swstate(tp_rfk);

	return (res < 0) ? res : 0;
}