#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ion_heap {int flags; TYPE_1__* ops; } ;
struct ion_device {int /*<<< orphan*/  buffer_lock; } ;
struct ion_buffer {unsigned long flags; unsigned long size; int /*<<< orphan*/  lock; int /*<<< orphan*/  attachments; int /*<<< orphan*/  sg_table; struct ion_device* dev; struct ion_heap* heap; } ;
struct TYPE_2__ {int (* allocate ) (struct ion_heap*,struct ion_buffer*,unsigned long,unsigned long) ;int /*<<< orphan*/  (* free ) (struct ion_buffer*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ion_buffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ION_HEAP_FLAG_DEFER_FREE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  ion_buffer_add (struct ion_device*,struct ion_buffer*) ; 
 int /*<<< orphan*/  ion_heap_freelist_drain (struct ion_heap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ion_buffer*) ; 
 struct ion_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ion_heap*,struct ion_buffer*,unsigned long,unsigned long) ; 
 int stub2 (struct ion_heap*,struct ion_buffer*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  stub3 (struct ion_buffer*) ; 

__attribute__((used)) static struct ion_buffer *ion_buffer_create(struct ion_heap *heap,
					    struct ion_device *dev,
					    unsigned long len,
					    unsigned long flags)
{
	struct ion_buffer *buffer;
	int ret;

	buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	buffer->heap = heap;
	buffer->flags = flags;
	buffer->dev = dev;
	buffer->size = len;

	ret = heap->ops->allocate(heap, buffer, len, flags);

	if (ret) {
		if (!(heap->flags & ION_HEAP_FLAG_DEFER_FREE))
			goto err2;

		ion_heap_freelist_drain(heap, 0);
		ret = heap->ops->allocate(heap, buffer, len, flags);
		if (ret)
			goto err2;
	}

	if (!buffer->sg_table) {
		WARN_ONCE(1, "This heap needs to set the sgtable");
		ret = -EINVAL;
		goto err1;
	}

	INIT_LIST_HEAD(&buffer->attachments);
	mutex_init(&buffer->lock);
	mutex_lock(&dev->buffer_lock);
	ion_buffer_add(dev, buffer);
	mutex_unlock(&dev->buffer_lock);
	return buffer;

err1:
	heap->ops->free(buffer);
err2:
	kfree(buffer);
	return ERR_PTR(ret);
}