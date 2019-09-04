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
struct orangefs_bufmap {int /*<<< orphan*/  readdir_index_array; int /*<<< orphan*/  buffer_index_array; int /*<<< orphan*/  desc_count; } ;
struct ORANGEFS_dev_map_desc {int size; int count; unsigned long total_size; scalar_t__ ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GOSSIP_BUFMAP_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_READDIR_DEFAULT_DESC_COUNT ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int PAGE_SIZE ; 
 struct orangefs_bufmap* __orangefs_bufmap ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gossip_err (char*,...) ; 
 int /*<<< orphan*/  install (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orangefs_bufmap* orangefs_bufmap_alloc (struct ORANGEFS_dev_map_desc*) ; 
 int /*<<< orphan*/  orangefs_bufmap_free (struct orangefs_bufmap*) ; 
 int /*<<< orphan*/  orangefs_bufmap_lock ; 
 int orangefs_bufmap_map (struct orangefs_bufmap*,struct ORANGEFS_dev_map_desc*) ; 
 int /*<<< orphan*/  orangefs_bufmap_unmap (struct orangefs_bufmap*) ; 
 int /*<<< orphan*/  readdir_map ; 
 int /*<<< orphan*/  rw_map ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int orangefs_bufmap_initialize(struct ORANGEFS_dev_map_desc *user_desc)
{
	struct orangefs_bufmap *bufmap;
	int ret = -EINVAL;

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "orangefs_bufmap_initialize: called (ptr ("
		     "%p) sz (%d) cnt(%d).\n",
		     user_desc->ptr,
		     user_desc->size,
		     user_desc->count);

	if (user_desc->total_size < 0 ||
	    user_desc->size < 0 ||
	    user_desc->count < 0)
		goto out;

	/*
	 * sanity check alignment and size of buffer that caller wants to
	 * work with
	 */
	if (PAGE_ALIGN((unsigned long)user_desc->ptr) !=
	    (unsigned long)user_desc->ptr) {
		gossip_err("orangefs error: memory alignment (front). %p\n",
			   user_desc->ptr);
		goto out;
	}

	if (PAGE_ALIGN(((unsigned long)user_desc->ptr + user_desc->total_size))
	    != (unsigned long)(user_desc->ptr + user_desc->total_size)) {
		gossip_err("orangefs error: memory alignment (back).(%p + %d)\n",
			   user_desc->ptr,
			   user_desc->total_size);
		goto out;
	}

	if (user_desc->total_size != (user_desc->size * user_desc->count)) {
		gossip_err("orangefs error: user provided an oddly sized buffer: (%d, %d, %d)\n",
			   user_desc->total_size,
			   user_desc->size,
			   user_desc->count);
		goto out;
	}

	if ((user_desc->size % PAGE_SIZE) != 0) {
		gossip_err("orangefs error: bufmap size not page size divisible (%d).\n",
			   user_desc->size);
		goto out;
	}

	ret = -ENOMEM;
	bufmap = orangefs_bufmap_alloc(user_desc);
	if (!bufmap)
		goto out;

	ret = orangefs_bufmap_map(bufmap, user_desc);
	if (ret)
		goto out_free_bufmap;


	spin_lock(&orangefs_bufmap_lock);
	if (__orangefs_bufmap) {
		spin_unlock(&orangefs_bufmap_lock);
		gossip_err("orangefs: error: bufmap already initialized.\n");
		ret = -EINVAL;
		goto out_unmap_bufmap;
	}
	__orangefs_bufmap = bufmap;
	install(&rw_map,
		bufmap->desc_count,
		bufmap->buffer_index_array);
	install(&readdir_map,
		ORANGEFS_READDIR_DEFAULT_DESC_COUNT,
		bufmap->readdir_index_array);
	spin_unlock(&orangefs_bufmap_lock);

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "orangefs_bufmap_initialize: exiting normally\n");
	return 0;

out_unmap_bufmap:
	orangefs_bufmap_unmap(bufmap);
out_free_bufmap:
	orangefs_bufmap_free(bufmap);
out:
	return ret;
}