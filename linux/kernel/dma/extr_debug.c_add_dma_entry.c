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
struct dma_debug_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int active_cacheline_insert (struct dma_debug_entry*) ; 
 struct hash_bucket* get_hash_bucket (struct dma_debug_entry*,unsigned long*) ; 
 int global_disable ; 
 int /*<<< orphan*/  hash_bucket_add (struct hash_bucket*,struct dma_debug_entry*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_hash_bucket (struct hash_bucket*,unsigned long*) ; 

__attribute__((used)) static void add_dma_entry(struct dma_debug_entry *entry)
{
	struct hash_bucket *bucket;
	unsigned long flags;
	int rc;

	bucket = get_hash_bucket(entry, &flags);
	hash_bucket_add(bucket, entry);
	put_hash_bucket(bucket, &flags);

	rc = active_cacheline_insert(entry);
	if (rc == -ENOMEM) {
		pr_err("cacheline tracking ENOMEM, dma-debug disabled\n");
		global_disable = true;
	}

	/* TODO: report -EEXIST errors here as overlapping mappings are
	 * not supported by the DMA API
	 */
}