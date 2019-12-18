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
struct hash_bucket {int dummy; } ;
struct dma_debug_entry {unsigned long long size; size_t direction; unsigned long long sg_call_ents; scalar_t__ type; struct device* dev; scalar_t__ dev_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t DMA_BIDIRECTIONAL ; 
 size_t DMA_FROM_DEVICE ; 
 size_t DMA_TO_DEVICE ; 
 struct dma_debug_entry* bucket_find_contain (struct hash_bucket**,struct dma_debug_entry*,unsigned long*) ; 
 int /*<<< orphan*/ * dir2name ; 
 scalar_t__ dma_debug_sg ; 
 int /*<<< orphan*/  err_printk (struct device*,struct dma_debug_entry*,char*,unsigned long long,unsigned long long,...) ; 
 struct hash_bucket* get_hash_bucket (struct dma_debug_entry*,unsigned long*) ; 
 int /*<<< orphan*/  put_hash_bucket (struct hash_bucket*,unsigned long*) ; 

__attribute__((used)) static void check_sync(struct device *dev,
		       struct dma_debug_entry *ref,
		       bool to_cpu)
{
	struct dma_debug_entry *entry;
	struct hash_bucket *bucket;
	unsigned long flags;

	bucket = get_hash_bucket(ref, &flags);

	entry = bucket_find_contain(&bucket, ref, &flags);

	if (!entry) {
		err_printk(dev, NULL, "device driver tries "
				"to sync DMA memory it has not allocated "
				"[device address=0x%016llx] [size=%llu bytes]\n",
				(unsigned long long)ref->dev_addr, ref->size);
		goto out;
	}

	if (ref->size > entry->size) {
		err_printk(dev, entry, "device driver syncs"
				" DMA memory outside allocated range "
				"[device address=0x%016llx] "
				"[allocation size=%llu bytes] "
				"[sync offset+size=%llu]\n",
				entry->dev_addr, entry->size,
				ref->size);
	}

	if (entry->direction == DMA_BIDIRECTIONAL)
		goto out;

	if (ref->direction != entry->direction) {
		err_printk(dev, entry, "device driver syncs "
				"DMA memory with different direction "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned long long)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);
	}

	if (to_cpu && !(entry->direction == DMA_FROM_DEVICE) &&
		      !(ref->direction == DMA_TO_DEVICE))
		err_printk(dev, entry, "device driver syncs "
				"device read-only DMA memory for cpu "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned long long)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);

	if (!to_cpu && !(entry->direction == DMA_TO_DEVICE) &&
		       !(ref->direction == DMA_FROM_DEVICE))
		err_printk(dev, entry, "device driver syncs "
				"device write-only DMA memory to device "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned long long)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);

	if (ref->sg_call_ents && ref->type == dma_debug_sg &&
	    ref->sg_call_ents != entry->sg_call_ents) {
		err_printk(ref->dev, entry, "device driver syncs "
			   "DMA sg list with different entry count "
			   "[map count=%d] [sync count=%d]\n",
			   entry->sg_call_ents, ref->sg_call_ents);
	}

out:
	put_hash_bucket(bucket, &flags);
}