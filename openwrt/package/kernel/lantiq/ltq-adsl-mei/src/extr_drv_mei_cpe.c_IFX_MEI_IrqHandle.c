#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int* CMV_RxMsg; int cmv_waiting; int arcmsgav; int modem_ready; int /*<<< orphan*/  wait_queue_modemready; scalar_t__ Recent_indicator; int /*<<< orphan*/  modem_ready_cnt; int /*<<< orphan*/  wait_queue_arcmsgav; } ;
struct TYPE_3__ {int /*<<< orphan*/  pData; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;
typedef  size_t DSL_BSP_CB_Type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_MEI_MAILBOXR ; 
 int /*<<< orphan*/  ARC_TO_MEI_MSGAV ; 
 int D2H_AUTONOMOUS_MODEM_READY_MSG ; 
 size_t DSL_BSP_CB_CEOC_IRQ ; 
 size_t DSL_BSP_CB_FIRMWARE_REBOOT ; 
 TYPE_2__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_DMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_DebugRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_MailboxRead (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MEI_WAKEUP_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ ME_ARC2ME_STAT ; 
 int MSG_LENGTH ; 
 int OMB_CLEAREOC_INTERRUPT_CODE ; 
 int OMB_CODESWAP_MESSAGE_MSG_TYPE_MASK ; 
 int OMB_REBOOT_INTERRUPT_CODE ; 
 int /*<<< orphan*/  dfe_loopback_irq_handler (int /*<<< orphan*/ *) ; 
 TYPE_1__* dsl_bsp_event_callback ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t IFX_MEI_IrqHandle (int int1, void *void0)
{
	u32 scratch;
	DSL_DEV_Device_t *pDev = (DSL_DEV_Device_t *) void0;
#if defined(CONFIG_LTQ_MEI_FW_LOOPBACK) && defined(DFE_PING_TEST)
	dfe_loopback_irq_handler (pDev);
	return IRQ_HANDLED;
#endif //CONFIG_AMAZON_S_MEI_FW_LOOPBACK
        DSL_BSP_CB_Type_t event;

	if (pDev == NULL)
		IFX_MEI_EMSG("Error: Got Interrupt but pDev is NULL!!!!\n");

	IFX_MEI_DebugRead (pDev, ARC_MEI_MAILBOXR, &scratch, 1);
	if (scratch & OMB_CODESWAP_MESSAGE_MSG_TYPE_MASK) {
		IFX_MEI_EMSG("Receive Code Swap Request interrupt!!!\n");
		return IRQ_HANDLED;
	}
	else if (scratch & OMB_CLEAREOC_INTERRUPT_CODE)	 {
		// clear eoc message interrupt
		IFX_MEI_DMSG("OMB_CLEAREOC_INTERRUPT_CODE\n");
                event = DSL_BSP_CB_CEOC_IRQ;
		IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ARC2ME_STAT, ARC_TO_MEI_MSGAV);
                if (dsl_bsp_event_callback[event].function)
			(*dsl_bsp_event_callback[event].function)(pDev, event, dsl_bsp_event_callback[event].pData);
        } else if (scratch & OMB_REBOOT_INTERRUPT_CODE) {
                // Reboot
                IFX_MEI_DMSG("OMB_REBOOT_INTERRUPT_CODE\n");
                event = DSL_BSP_CB_FIRMWARE_REBOOT;

		IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ARC2ME_STAT, ARC_TO_MEI_MSGAV);

                if (dsl_bsp_event_callback[event].function)
                        (*dsl_bsp_event_callback[event].function)(pDev, event, dsl_bsp_event_callback[event].pData);
        } else { // normal message
                IFX_MEI_MailboxRead (pDev, DSL_DEV_PRIVATE(pDev)->CMV_RxMsg, MSG_LENGTH);
                if (DSL_DEV_PRIVATE(pDev)-> cmv_waiting == 1) {
                        DSL_DEV_PRIVATE(pDev)-> arcmsgav = 1;
                        DSL_DEV_PRIVATE(pDev)-> cmv_waiting = 0;
#if !defined(BSP_PORT_RTEMS)
                        MEI_WAKEUP_EVENT (DSL_DEV_PRIVATE(pDev)->wait_queue_arcmsgav);
#endif
                }
		else {
			DSL_DEV_PRIVATE(pDev)-> modem_ready_cnt++;
			memcpy ((char *) DSL_DEV_PRIVATE(pDev)->Recent_indicator,
				(char *) DSL_DEV_PRIVATE(pDev)->CMV_RxMsg, MSG_LENGTH * 2);
			if (((DSL_DEV_PRIVATE(pDev)->CMV_RxMsg[0] & 0xff0) >> 4) == D2H_AUTONOMOUS_MODEM_READY_MSG) {
				//check ARC ready message
				IFX_MEI_DMSG ("Got MODEM_READY_MSG\n");
				DSL_DEV_PRIVATE(pDev)->modem_ready = 1;
				MEI_WAKEUP_EVENT (DSL_DEV_PRIVATE(pDev)->wait_queue_modemready);
			}
		}
	}

	return IRQ_HANDLED;
}