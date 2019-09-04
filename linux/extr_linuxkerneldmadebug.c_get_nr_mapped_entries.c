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
struct dma_debug_entry {int sg_mapped_ents; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct dma_debug_entry* bucket_find_exact (struct hash_bucket*,struct dma_debug_entry*) ; 
 struct hash_bucket* get_hash_bucket (struct dma_debug_entry*,unsigned long*) ; 
 int /*<<< orphan*/  put_hash_bucket (struct hash_bucket*,unsigned long*) ; 

__attribute__((used)) static int get_nr_mapped_entries(struct device *dev,
				 struct dma_debug_entry *ref)
{
	struct dma_debug_entry *entry;
	struct hash_bucket *bucket;
	unsigned long flags;
	int mapped_ents;

	bucket       = get_hash_bucket(ref, &flags);
	entry        = bucket_find_exact(bucket, ref);
	mapped_ents  = 0;

	if (entry)
		mapped_ents = entry->sg_mapped_ents;
	put_hash_bucket(bucket, &flags);

	return mapped_ents;
}