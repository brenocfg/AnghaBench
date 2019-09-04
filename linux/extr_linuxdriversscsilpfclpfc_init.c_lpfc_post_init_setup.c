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
struct lpfc_hba {int sli3_options; int cfg_poll; scalar_t__ cfg_hba_queue_depth; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  ModelDesc; int /*<<< orphan*/  ModelName; } ;
struct lpfc_adapter_event_header {int /*<<< orphan*/  subcategory; int /*<<< orphan*/  event_type; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ can_queue; } ;
typedef  int /*<<< orphan*/  adapter_event ;

/* Variables and functions */
 int DISABLE_FCP_RING_INT ; 
 int /*<<< orphan*/  FC_REG_ADAPTER_EVENT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_EVENT_ARRIVAL ; 
 int /*<<< orphan*/  LPFC_NL_VENDOR_ID ; 
 int LPFC_SLI3_BG_ENABLED ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_vendor_event (struct Scsi_Host*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_get_hba_model_desc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_host_attrib_init (struct Scsi_Host*) ; 
 int /*<<< orphan*/  lpfc_poll_start_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_setup_bg (struct lpfc_hba*,struct Scsi_Host*) ; 
 struct Scsi_Host* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_post_init_setup(struct lpfc_hba *phba)
{
	struct Scsi_Host  *shost;
	struct lpfc_adapter_event_header adapter_event;

	/* Get the default values for Model Name and Description */
	lpfc_get_hba_model_desc(phba, phba->ModelName, phba->ModelDesc);

	/*
	 * hba setup may have changed the hba_queue_depth so we need to
	 * adjust the value of can_queue.
	 */
	shost = pci_get_drvdata(phba->pcidev);
	shost->can_queue = phba->cfg_hba_queue_depth - 10;
	if (phba->sli3_options & LPFC_SLI3_BG_ENABLED)
		lpfc_setup_bg(phba, shost);

	lpfc_host_attrib_init(shost);

	if (phba->cfg_poll & DISABLE_FCP_RING_INT) {
		spin_lock_irq(shost->host_lock);
		lpfc_poll_start_timer(phba);
		spin_unlock_irq(shost->host_lock);
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"0428 Perform SCSI scan\n");
	/* Send board arrival event to upper layer */
	adapter_event.event_type = FC_REG_ADAPTER_EVENT;
	adapter_event.subcategory = LPFC_EVENT_ARRIVAL;
	fc_host_post_vendor_event(shost, fc_get_event_number(),
				  sizeof(adapter_event),
				  (char *) &adapter_event,
				  LPFC_NL_VENDOR_ID);
	return;
}