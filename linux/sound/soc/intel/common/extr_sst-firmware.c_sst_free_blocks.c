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
struct sst_dsp {int /*<<< orphan*/  mutex; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_list_remove (struct sst_dsp*,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sst_free_blocks(struct sst_dsp *dsp, struct list_head *block_list)
{
	mutex_lock(&dsp->mutex);
	block_list_remove(dsp, block_list);
	mutex_unlock(&dsp->mutex);
	return 0;
}