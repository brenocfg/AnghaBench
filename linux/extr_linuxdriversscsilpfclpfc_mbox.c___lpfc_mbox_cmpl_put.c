#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mboxq_cmpl; } ;
struct lpfc_hba {TYPE_1__ sli; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
__lpfc_mbox_cmpl_put(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbq)
{
	list_add_tail(&mbq->list, &phba->sli.mboxq_cmpl);
}