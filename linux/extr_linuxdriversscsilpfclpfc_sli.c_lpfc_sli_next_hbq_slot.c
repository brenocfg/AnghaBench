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
typedef  size_t uint32_t ;
struct lpfc_hbq_entry {int dummy; } ;
struct lpfc_hba {size_t* hbq_get; struct hbq_s* hbqs; int /*<<< orphan*/  link_state; int /*<<< orphan*/  hbalock; } ;
struct hbq_s {scalar_t__ next_hbqPutIdx; scalar_t__ hbqPutIdx; scalar_t__ entry_count; scalar_t__ local_hbqGetIdx; scalar_t__ hbq_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_SLI ; 
 int LOG_VPORT ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 size_t le32_to_cpu (size_t) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,size_t,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct lpfc_hbq_entry *
lpfc_sli_next_hbq_slot(struct lpfc_hba *phba, uint32_t hbqno)
{
	struct hbq_s *hbqp = &phba->hbqs[hbqno];

	lockdep_assert_held(&phba->hbalock);

	if (hbqp->next_hbqPutIdx == hbqp->hbqPutIdx &&
	    ++hbqp->next_hbqPutIdx >= hbqp->entry_count)
		hbqp->next_hbqPutIdx = 0;

	if (unlikely(hbqp->local_hbqGetIdx == hbqp->next_hbqPutIdx)) {
		uint32_t raw_index = phba->hbq_get[hbqno];
		uint32_t getidx = le32_to_cpu(raw_index);

		hbqp->local_hbqGetIdx = getidx;

		if (unlikely(hbqp->local_hbqGetIdx >= hbqp->entry_count)) {
			lpfc_printf_log(phba, KERN_ERR,
					LOG_SLI | LOG_VPORT,
					"1802 HBQ %d: local_hbqGetIdx "
					"%u is > than hbqp->entry_count %u\n",
					hbqno, hbqp->local_hbqGetIdx,
					hbqp->entry_count);

			phba->link_state = LPFC_HBA_ERROR;
			return NULL;
		}

		if (hbqp->local_hbqGetIdx == hbqp->next_hbqPutIdx)
			return NULL;
	}

	return (struct lpfc_hbq_entry *) phba->hbqs[hbqno].hbq_virt +
			hbqp->hbqPutIdx;
}