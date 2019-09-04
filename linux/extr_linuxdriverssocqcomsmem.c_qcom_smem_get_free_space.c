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
struct smem_partition_header {int /*<<< orphan*/  offset_free_uncached; int /*<<< orphan*/  offset_free_cached; } ;
struct smem_header {int /*<<< orphan*/  available; } ;
struct TYPE_4__ {TYPE_1__* regions; struct smem_partition_header* global_partition; struct smem_partition_header** partitions; } ;
struct TYPE_3__ {struct smem_header* virt_base; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 unsigned int SMEM_HOST_COUNT ; 
 TYPE_2__* __smem ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

int qcom_smem_get_free_space(unsigned host)
{
	struct smem_partition_header *phdr;
	struct smem_header *header;
	unsigned ret;

	if (!__smem)
		return -EPROBE_DEFER;

	if (host < SMEM_HOST_COUNT && __smem->partitions[host]) {
		phdr = __smem->partitions[host];
		ret = le32_to_cpu(phdr->offset_free_cached) -
		      le32_to_cpu(phdr->offset_free_uncached);
	} else if (__smem->global_partition) {
		phdr = __smem->global_partition;
		ret = le32_to_cpu(phdr->offset_free_cached) -
		      le32_to_cpu(phdr->offset_free_uncached);
	} else {
		header = __smem->regions[0].virt_base;
		ret = le32_to_cpu(header->available);
	}

	return ret;
}