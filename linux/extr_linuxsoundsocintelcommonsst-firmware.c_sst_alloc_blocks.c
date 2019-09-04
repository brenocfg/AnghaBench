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
struct sst_dsp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct sst_block_allocator {int /*<<< orphan*/  type; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int block_alloc (struct sst_dsp*,struct sst_block_allocator*,struct list_head*) ; 
 int block_list_prepare (struct sst_dsp*,struct list_head*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sst_alloc_blocks(struct sst_dsp *dsp, struct sst_block_allocator *ba,
	struct list_head *block_list)
{
	int ret;

	dev_dbg(dsp->dev, "block request 0x%x bytes at offset 0x%x type %d\n",
		ba->size, ba->offset, ba->type);

	mutex_lock(&dsp->mutex);

	ret = block_alloc(dsp, ba, block_list);
	if (ret < 0) {
		dev_err(dsp->dev, "error: can't alloc blocks %d\n", ret);
		goto out;
	}

	/* prepare DSP blocks for module usage */
	ret = block_list_prepare(dsp, block_list);
	if (ret < 0)
		dev_err(dsp->dev, "error: prepare failed\n");

out:
	mutex_unlock(&dsp->mutex);
	return ret;
}