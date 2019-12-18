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
struct page {int dummy; } ;
struct orangefs_bufmap_desc {int dummy; } ;
struct orangefs_bufmap {int total_size; int desc_count; int page_count; struct orangefs_bufmap* buffer_index_array; struct orangefs_bufmap* desc_array; void* page_array; int /*<<< orphan*/  desc_size; int /*<<< orphan*/  desc_shift; } ;
struct ORANGEFS_dev_map_desc {int total_size; int count; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct orangefs_bufmap*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct orangefs_bufmap *
orangefs_bufmap_alloc(struct ORANGEFS_dev_map_desc *user_desc)
{
	struct orangefs_bufmap *bufmap;

	bufmap = kzalloc(sizeof(*bufmap), GFP_KERNEL);
	if (!bufmap)
		goto out;

	bufmap->total_size = user_desc->total_size;
	bufmap->desc_count = user_desc->count;
	bufmap->desc_size = user_desc->size;
	bufmap->desc_shift = ilog2(bufmap->desc_size);

	bufmap->buffer_index_array =
		kzalloc(DIV_ROUND_UP(bufmap->desc_count, BITS_PER_LONG), GFP_KERNEL);
	if (!bufmap->buffer_index_array)
		goto out_free_bufmap;

	bufmap->desc_array =
		kcalloc(bufmap->desc_count, sizeof(struct orangefs_bufmap_desc),
			GFP_KERNEL);
	if (!bufmap->desc_array)
		goto out_free_index_array;

	bufmap->page_count = bufmap->total_size / PAGE_SIZE;

	/* allocate storage to track our page mappings */
	bufmap->page_array =
		kcalloc(bufmap->page_count, sizeof(struct page *), GFP_KERNEL);
	if (!bufmap->page_array)
		goto out_free_desc_array;

	return bufmap;

out_free_desc_array:
	kfree(bufmap->desc_array);
out_free_index_array:
	kfree(bufmap->buffer_index_array);
out_free_bufmap:
	kfree(bufmap);
out:
	return NULL;
}