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
typedef  unsigned int u32 ;
struct smem_ptable_entry {int /*<<< orphan*/  cacheline; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; } ;
struct smem_ptable {struct smem_ptable_entry* entry; int /*<<< orphan*/  num_entries; } ;
struct smem_partition_header {int /*<<< orphan*/  size; int /*<<< orphan*/  offset_free_uncached; int /*<<< orphan*/  magic; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; } ;
struct qcom_smem {int* cacheline; struct smem_partition_header** partitions; int /*<<< orphan*/  dev; TYPE_1__* regions; } ;
struct TYPE_2__ {struct smem_partition_header* virt_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct smem_ptable*) ; 
 int PTR_ERR (struct smem_ptable*) ; 
 unsigned int SMEM_HOST_COUNT ; 
 int /*<<< orphan*/  SMEM_PART_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct smem_ptable* qcom_smem_get_ptable (struct qcom_smem*) ; 

__attribute__((used)) static int qcom_smem_enumerate_partitions(struct qcom_smem *smem,
					  unsigned int local_host)
{
	struct smem_partition_header *header;
	struct smem_ptable_entry *entry;
	struct smem_ptable *ptable;
	unsigned int remote_host;
	u32 host0, host1;
	int i;

	ptable = qcom_smem_get_ptable(smem);
	if (IS_ERR(ptable))
		return PTR_ERR(ptable);

	for (i = 0; i < le32_to_cpu(ptable->num_entries); i++) {
		entry = &ptable->entry[i];
		host0 = le16_to_cpu(entry->host0);
		host1 = le16_to_cpu(entry->host1);

		if (host0 != local_host && host1 != local_host)
			continue;

		if (!le32_to_cpu(entry->offset))
			continue;

		if (!le32_to_cpu(entry->size))
			continue;

		if (host0 == local_host)
			remote_host = host1;
		else
			remote_host = host0;

		if (remote_host >= SMEM_HOST_COUNT) {
			dev_err(smem->dev,
				"Invalid remote host %d\n",
				remote_host);
			return -EINVAL;
		}

		if (smem->partitions[remote_host]) {
			dev_err(smem->dev,
				"Already found a partition for host %d\n",
				remote_host);
			return -EINVAL;
		}

		header = smem->regions[0].virt_base + le32_to_cpu(entry->offset);
		host0 = le16_to_cpu(header->host0);
		host1 = le16_to_cpu(header->host1);

		if (memcmp(header->magic, SMEM_PART_MAGIC,
			    sizeof(header->magic))) {
			dev_err(smem->dev,
				"Partition %d has invalid magic\n", i);
			return -EINVAL;
		}

		if (host0 != local_host && host1 != local_host) {
			dev_err(smem->dev,
				"Partition %d hosts are invalid\n", i);
			return -EINVAL;
		}

		if (host0 != remote_host && host1 != remote_host) {
			dev_err(smem->dev,
				"Partition %d hosts are invalid\n", i);
			return -EINVAL;
		}

		if (le32_to_cpu(header->size) != le32_to_cpu(entry->size)) {
			dev_err(smem->dev,
				"Partition %d has invalid size\n", i);
			return -EINVAL;
		}

		if (le32_to_cpu(header->offset_free_uncached) > le32_to_cpu(header->size)) {
			dev_err(smem->dev,
				"Partition %d has invalid free pointer\n", i);
			return -EINVAL;
		}

		smem->partitions[remote_host] = header;
		smem->cacheline[remote_host] = le32_to_cpu(entry->cacheline);
	}

	return 0;
}