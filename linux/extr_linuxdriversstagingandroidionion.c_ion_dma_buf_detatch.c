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
struct ion_dma_buf_attachment {int /*<<< orphan*/  table; int /*<<< orphan*/  list; } ;
struct ion_buffer {int /*<<< orphan*/  lock; } ;
struct dma_buf_attachment {struct ion_dma_buf_attachment* priv; } ;
struct dma_buf {struct ion_buffer* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_duped_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ion_dma_buf_attachment*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ion_dma_buf_detatch(struct dma_buf *dmabuf,
				struct dma_buf_attachment *attachment)
{
	struct ion_dma_buf_attachment *a = attachment->priv;
	struct ion_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	list_del(&a->list);
	mutex_unlock(&buffer->lock);
	free_duped_table(a->table);

	kfree(a);
}