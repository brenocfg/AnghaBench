#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_33__ {scalar_t__ prtpwr; } ;
struct TYPE_23__ {int /*<<< orphan*/  d32; TYPE_5__ b; } ;
typedef  TYPE_11__ hprt0_data_t ;
struct TYPE_36__ {int chdis; scalar_t__ epdir; scalar_t__ chen; } ;
struct TYPE_24__ {int /*<<< orphan*/  d32; TYPE_8__ b; } ;
typedef  TYPE_12__ hcchar_data_t ;
struct TYPE_31__ {int nptxfempty; int ptxfempty; int hcintr; } ;
struct TYPE_25__ {scalar_t__ d32; TYPE_3__ b; } ;
typedef  TYPE_13__ gintsts_data_t ;
struct TYPE_29__ {int port_connect_status_change; scalar_t__ port_connect_status; } ;
struct TYPE_30__ {TYPE_1__ b; } ;
struct TYPE_26__ {int /*<<< orphan*/  lock; TYPE_10__* fops; TYPE_9__* fiq_state; scalar_t__* hub_port; TYPE_18__* core_if; int /*<<< orphan*/ ** hc_ptr_array; TYPE_2__ flags; } ;
typedef  TYPE_14__ dwc_otg_hcd_t ;
struct TYPE_27__ {int /*<<< orphan*/  hcchar; } ;
typedef  TYPE_15__ dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_hc_t ;
struct TYPE_37__ {int /*<<< orphan*/  lock; } ;
struct TYPE_35__ {TYPE_15__** hc_regs; int /*<<< orphan*/ * hprt0; } ;
struct TYPE_34__ {int host_channels; } ;
struct TYPE_32__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;
struct TYPE_28__ {scalar_t__ op_state; TYPE_7__* host_if; int /*<<< orphan*/  dma_enable; TYPE_6__* core_params; TYPE_4__* core_global_regs; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* disconnect ) (TYPE_14__*) ;} ;

/* Variables and functions */
 scalar_t__ A_SUSPEND ; 
 scalar_t__ DWC_CIRCLEQ_EMPTY_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timers (TYPE_14__*) ; 
 int /*<<< orphan*/  dwc_otg_disable_host_interrupts (TYPE_18__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_18__*) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_18__*) ; 
 scalar_t__ fiq_enable ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_list_entry ; 
 int /*<<< orphan*/  kill_all_urbs (TYPE_14__*) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  stub1 (TYPE_14__*) ; 

__attribute__((used)) static int32_t dwc_otg_hcd_disconnect_cb(void *p)
{
	gintsts_data_t intr;
	dwc_otg_hcd_t *dwc_otg_hcd = p;

	DWC_SPINLOCK(dwc_otg_hcd->lock);
	/*
	 * Set status flags for the hub driver.
	 */
	dwc_otg_hcd->flags.b.port_connect_status_change = 1;
	dwc_otg_hcd->flags.b.port_connect_status = 0;
	if(fiq_enable) {
		local_fiq_disable();
		fiq_fsm_spin_lock(&dwc_otg_hcd->fiq_state->lock);
	}
	/*
	 * Shutdown any transfers in process by clearing the Tx FIFO Empty
	 * interrupt mask and status bits and disabling subsequent host
	 * channel interrupts.
	 */
	intr.d32 = 0;
	intr.b.nptxfempty = 1;
	intr.b.ptxfempty = 1;
	intr.b.hcintr = 1;
	DWC_MODIFY_REG32(&dwc_otg_hcd->core_if->core_global_regs->gintmsk,
			 intr.d32, 0);
	DWC_MODIFY_REG32(&dwc_otg_hcd->core_if->core_global_regs->gintsts,
			 intr.d32, 0);

	del_timers(dwc_otg_hcd);

	/*
	 * Turn off the vbus power only if the core has transitioned to device
	 * mode. If still in host mode, need to keep power on to detect a
	 * reconnection.
	 */
	if (dwc_otg_is_device_mode(dwc_otg_hcd->core_if)) {
		if (dwc_otg_hcd->core_if->op_state != A_SUSPEND) {
			hprt0_data_t hprt0 = {.d32 = 0 };
			DWC_PRINTF("Disconnect: PortPower off\n");
			hprt0.b.prtpwr = 0;
			DWC_WRITE_REG32(dwc_otg_hcd->core_if->host_if->hprt0,
					hprt0.d32);
		}

		dwc_otg_disable_host_interrupts(dwc_otg_hcd->core_if);
	}

	/* Respond with an error status to all URBs in the schedule. */
	kill_all_urbs(dwc_otg_hcd);

	if (dwc_otg_is_host_mode(dwc_otg_hcd->core_if)) {
		/* Clean up any host channels that were in use. */
		int num_channels;
		int i;
		dwc_hc_t *channel;
		dwc_otg_hc_regs_t *hc_regs;
		hcchar_data_t hcchar;

		num_channels = dwc_otg_hcd->core_if->core_params->host_channels;

		if (!dwc_otg_hcd->core_if->dma_enable) {
			/* Flush out any channel requests in slave mode. */
			for (i = 0; i < num_channels; i++) {
				channel = dwc_otg_hcd->hc_ptr_array[i];
				if (DWC_CIRCLEQ_EMPTY_ENTRY
				    (channel, hc_list_entry)) {
					hc_regs =
					    dwc_otg_hcd->core_if->
					    host_if->hc_regs[i];
					hcchar.d32 =
					    DWC_READ_REG32(&hc_regs->hcchar);
					if (hcchar.b.chen) {
						hcchar.b.chen = 0;
						hcchar.b.chdis = 1;
						hcchar.b.epdir = 0;
						DWC_WRITE_REG32
						    (&hc_regs->hcchar,
						     hcchar.d32);
					}
				}
			}
		}

		if(fiq_fsm_enable) {
			for(i=0; i < 128; i++) {
				dwc_otg_hcd->hub_port[i] = 0;
			}
		}
	}

	if(fiq_enable) {
		fiq_fsm_spin_unlock(&dwc_otg_hcd->fiq_state->lock);
		local_fiq_enable();
	}

	if (dwc_otg_hcd->fops->disconnect) {
		dwc_otg_hcd->fops->disconnect(dwc_otg_hcd);
	}

	DWC_SPINUNLOCK(dwc_otg_hcd->lock);
	return 1;
}