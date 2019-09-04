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
struct lpfc_hba {int /*<<< orphan*/  pport; } ;
struct lpfc_board_event_header {int /*<<< orphan*/  subcategory; int /*<<< orphan*/  event_type; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  board_event ;

/* Variables and functions */
 int /*<<< orphan*/  FC_REG_BOARD_EVENT ; 
 int /*<<< orphan*/  LPFC_EVENT_PORTINTERR ; 
 int /*<<< orphan*/  LPFC_NL_VENDOR_ID ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_vendor_event (struct Scsi_Host*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_board_errevt_to_mgmt(struct lpfc_hba *phba)
{
	struct lpfc_board_event_header board_event;
	struct Scsi_Host *shost;

	board_event.event_type = FC_REG_BOARD_EVENT;
	board_event.subcategory = LPFC_EVENT_PORTINTERR;
	shost = lpfc_shost_from_vport(phba->pport);
	fc_host_post_vendor_event(shost, fc_get_event_number(),
				  sizeof(board_event),
				  (char *) &board_event,
				  LPFC_NL_VENDOR_ID);
}