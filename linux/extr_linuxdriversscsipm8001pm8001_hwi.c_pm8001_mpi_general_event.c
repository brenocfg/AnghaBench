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
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_hba_info {int dummy; } ;
struct general_event_resp {int /*<<< orphan*/ * inb_IOMB_payload; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int GENERAL_EVENT_PAYLOAD ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int,...) ; 

int pm8001_mpi_general_event(struct pm8001_hba_info *pm8001_ha , void *piomb)
{
	u32 status;
	int i;
	struct general_event_resp *pPayload =
		(struct general_event_resp *)(piomb + 4);
	status = le32_to_cpu(pPayload->status);
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk(" status = 0x%x\n", status));
	for (i = 0; i < GENERAL_EVENT_PAYLOAD; i++)
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("inb_IOMB_payload[0x%x] 0x%x,\n", i,
			pPayload->inb_IOMB_payload[i]));
	return 0;
}