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
struct hisi_hba {unsigned int slot_index_count; int last_slot_index; void* slot_index_tags; } ;

/* Variables and functions */
 int SAS_QUEUE_FULL ; 
 unsigned int find_next_zero_bit (void*,unsigned int,int) ; 
 int /*<<< orphan*/  hisi_sas_slot_index_set (struct hisi_hba*,unsigned int) ; 

__attribute__((used)) static int hisi_sas_slot_index_alloc(struct hisi_hba *hisi_hba, int *slot_idx)
{
	unsigned int index;
	void *bitmap = hisi_hba->slot_index_tags;

	index = find_next_zero_bit(bitmap, hisi_hba->slot_index_count,
			hisi_hba->last_slot_index + 1);
	if (index >= hisi_hba->slot_index_count) {
		index = find_next_zero_bit(bitmap, hisi_hba->slot_index_count,
					   0);
		if (index >= hisi_hba->slot_index_count)
			return -SAS_QUEUE_FULL;
	}
	hisi_sas_slot_index_set(hisi_hba, index);
	*slot_idx = index;
	hisi_hba->last_slot_index = index;

	return 0;
}