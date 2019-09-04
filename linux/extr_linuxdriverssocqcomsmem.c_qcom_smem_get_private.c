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
struct smem_private_entry {scalar_t__ canary; int /*<<< orphan*/  padding_data; int /*<<< orphan*/  size; int /*<<< orphan*/  item; } ;
struct smem_partition_header {int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; } ;
struct qcom_smem {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ SMEM_PRIVATE_CANARY ; 
 struct smem_private_entry* cached_entry_next (struct smem_private_entry*,size_t) ; 
 void* cached_entry_to_item (struct smem_private_entry*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct smem_private_entry* phdr_to_first_cached_entry (struct smem_partition_header*,size_t) ; 
 struct smem_private_entry* phdr_to_first_uncached_entry (struct smem_partition_header*) ; 
 struct smem_private_entry* phdr_to_last_cached_entry (struct smem_partition_header*) ; 
 struct smem_private_entry* phdr_to_last_uncached_entry (struct smem_partition_header*) ; 
 struct smem_private_entry* uncached_entry_next (struct smem_private_entry*) ; 
 void* uncached_entry_to_item (struct smem_private_entry*) ; 

__attribute__((used)) static void *qcom_smem_get_private(struct qcom_smem *smem,
				   struct smem_partition_header *phdr,
				   size_t cacheline,
				   unsigned item,
				   size_t *size)
{
	struct smem_private_entry *e, *end;

	e = phdr_to_first_uncached_entry(phdr);
	end = phdr_to_last_uncached_entry(phdr);

	while (e < end) {
		if (e->canary != SMEM_PRIVATE_CANARY)
			goto invalid_canary;

		if (le16_to_cpu(e->item) == item) {
			if (size != NULL)
				*size = le32_to_cpu(e->size) -
					le16_to_cpu(e->padding_data);

			return uncached_entry_to_item(e);
		}

		e = uncached_entry_next(e);
	}

	/* Item was not found in the uncached list, search the cached list */

	e = phdr_to_first_cached_entry(phdr, cacheline);
	end = phdr_to_last_cached_entry(phdr);

	while (e > end) {
		if (e->canary != SMEM_PRIVATE_CANARY)
			goto invalid_canary;

		if (le16_to_cpu(e->item) == item) {
			if (size != NULL)
				*size = le32_to_cpu(e->size) -
					le16_to_cpu(e->padding_data);

			return cached_entry_to_item(e);
		}

		e = cached_entry_next(e, cacheline);
	}

	return ERR_PTR(-ENOENT);

invalid_canary:
	dev_err(smem->dev, "Found invalid canary in hosts %hu:%hu partition\n",
			le16_to_cpu(phdr->host0), le16_to_cpu(phdr->host1));

	return ERR_PTR(-EINVAL);
}