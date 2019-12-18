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
typedef  void* u32 ;
struct sst_mem_block {int type; int /*<<< orphan*/  list; struct sst_block_ops const* ops; void* private; struct sst_dsp* dsp; void* index; void* size; void* offset; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  free_block_list; } ;
struct sst_block_ops {int dummy; } ;
typedef  enum sst_mem_type { ____Placeholder_sst_mem_type } sst_mem_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sst_mem_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct sst_mem_block *sst_mem_block_register(struct sst_dsp *dsp, u32 offset,
	u32 size, enum sst_mem_type type, const struct sst_block_ops *ops,
	u32 index, void *private)
{
	struct sst_mem_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (block == NULL)
		return NULL;

	block->offset = offset;
	block->size = size;
	block->index = index;
	block->type = type;
	block->dsp = dsp;
	block->private = private;
	block->ops = ops;

	mutex_lock(&dsp->mutex);
	list_add(&block->list, &dsp->free_block_list);
	mutex_unlock(&dsp->mutex);

	return block;
}