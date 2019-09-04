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
typedef  scalar_t__ u32 ;
struct smem_ptable_entry {int /*<<< orphan*/  cacheline; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; } ;
struct smem_ptable {struct smem_ptable_entry* entry; int /*<<< orphan*/  num_entries; } ;
struct smem_partition_header {int /*<<< orphan*/  size; int /*<<< orphan*/  offset_free_uncached; int /*<<< orphan*/  magic; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; } ;
struct qcom_smem {scalar_t__ global_cacheline; struct smem_partition_header* global_partition; int /*<<< orphan*/  dev; TYPE_1__* regions; } ;
struct TYPE_2__ {struct smem_partition_header* virt_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct smem_ptable*) ; 
 int PTR_ERR (struct smem_ptable*) ; 
 scalar_t__ SMEM_GLOBAL_HOST ; 
 int /*<<< orphan*/  SMEM_PART_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct smem_ptable* qcom_smem_get_ptable (struct qcom_smem*) ; 

__attribute__((used)) static int qcom_smem_set_global_partition(struct qcom_smem *smem)
{
	struct smem_partition_header *header;
	struct smem_ptable_entry *entry;
	struct smem_ptable *ptable;
	u32 host0, host1, size;
	bool found = false;
	int i;

	if (smem->global_partition) {
		dev_err(smem->dev, "Already found the global partition\n");
		return -EINVAL;
	}

	ptable = qcom_smem_get_ptable(smem);
	if (IS_ERR(ptable))
		return PTR_ERR(ptable);

	for (i = 0; i < le32_to_cpu(ptable->num_entries); i++) {
		entry = &ptable->entry[i];
		host0 = le16_to_cpu(entry->host0);
		host1 = le16_to_cpu(entry->host1);

		if (host0 == SMEM_GLOBAL_HOST && host0 == host1) {
			found = true;
			break;
		}
	}

	if (!found) {
		dev_err(smem->dev, "Missing entry for global partition\n");
		return -EINVAL;
	}

	if (!le32_to_cpu(entry->offset) || !le32_to_cpu(entry->size)) {
		dev_err(smem->dev, "Invalid entry for global partition\n");
		return -EINVAL;
	}

	header = smem->regions[0].virt_base + le32_to_cpu(entry->offset);
	host0 = le16_to_cpu(header->host0);
	host1 = le16_to_cpu(header->host1);

	if (memcmp(header->magic, SMEM_PART_MAGIC, sizeof(header->magic))) {
		dev_err(smem->dev, "Global partition has invalid magic\n");
		return -EINVAL;
	}

	if (host0 != SMEM_GLOBAL_HOST && host1 != SMEM_GLOBAL_HOST) {
		dev_err(smem->dev, "Global partition hosts are invalid\n");
		return -EINVAL;
	}

	if (le32_to_cpu(header->size) != le32_to_cpu(entry->size)) {
		dev_err(smem->dev, "Global partition has invalid size\n");
		return -EINVAL;
	}

	size = le32_to_cpu(header->offset_free_uncached);
	if (size > le32_to_cpu(header->size)) {
		dev_err(smem->dev,
			"Global partition has invalid free pointer\n");
		return -EINVAL;
	}

	smem->global_partition = header;
	smem->global_cacheline = le32_to_cpu(entry->cacheline);

	return 0;
}