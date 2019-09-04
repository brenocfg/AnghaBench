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
struct efx_nic {scalar_t__ state; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  net_dev; TYPE_1__* type; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
struct TYPE_2__ {int (* map_reset_reason ) (int) ;} ;

/* Variables and functions */
 scalar_t__ READ_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  RESET_TYPE (int) ; 
#define  RESET_TYPE_ALL 136 
#define  RESET_TYPE_DATAPATH 135 
#define  RESET_TYPE_DISABLE 134 
#define  RESET_TYPE_INVISIBLE 133 
#define  RESET_TYPE_MCDI_TIMEOUT 132 
#define  RESET_TYPE_MC_BIST 131 
#define  RESET_TYPE_RECOVER_OR_ALL 130 
#define  RESET_TYPE_RECOVER_OR_DISABLE 129 
#define  RESET_TYPE_WORLD 128 
 scalar_t__ STATE_READY ; 
 scalar_t__ STATE_RECOVERY ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_mcdi_mode_poll (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_workqueue ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int stub1 (int) ; 

void efx_schedule_reset(struct efx_nic *efx, enum reset_type type)
{
	enum reset_type method;

	if (efx->state == STATE_RECOVERY) {
		netif_dbg(efx, drv, efx->net_dev,
			  "recovering: skip scheduling %s reset\n",
			  RESET_TYPE(type));
		return;
	}

	switch (type) {
	case RESET_TYPE_INVISIBLE:
	case RESET_TYPE_ALL:
	case RESET_TYPE_RECOVER_OR_ALL:
	case RESET_TYPE_WORLD:
	case RESET_TYPE_DISABLE:
	case RESET_TYPE_RECOVER_OR_DISABLE:
	case RESET_TYPE_DATAPATH:
	case RESET_TYPE_MC_BIST:
	case RESET_TYPE_MCDI_TIMEOUT:
		method = type;
		netif_dbg(efx, drv, efx->net_dev, "scheduling %s reset\n",
			  RESET_TYPE(method));
		break;
	default:
		method = efx->type->map_reset_reason(type);
		netif_dbg(efx, drv, efx->net_dev,
			  "scheduling %s reset for %s\n",
			  RESET_TYPE(method), RESET_TYPE(type));
		break;
	}

	set_bit(method, &efx->reset_pending);
	smp_mb(); /* ensure we change reset_pending before checking state */

	/* If we're not READY then just leave the flags set as the cue
	 * to abort probing or reschedule the reset later.
	 */
	if (READ_ONCE(efx->state) != STATE_READY)
		return;

	/* efx_process_channel() will no longer read events once a
	 * reset is scheduled. So switch back to poll'd MCDI completions. */
	efx_mcdi_mode_poll(efx);

	queue_work(reset_workqueue, &efx->reset_work);
}