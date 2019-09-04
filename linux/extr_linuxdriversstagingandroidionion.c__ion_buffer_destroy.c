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
struct ion_heap {int flags; } ;
struct ion_device {int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  buffers; } ;
struct ion_buffer {int /*<<< orphan*/  node; struct ion_device* dev; struct ion_heap* heap; } ;

/* Variables and functions */
 int ION_HEAP_FLAG_DEFER_FREE ; 
 int /*<<< orphan*/  ion_buffer_destroy (struct ion_buffer*) ; 
 int /*<<< orphan*/  ion_heap_freelist_add (struct ion_heap*,struct ion_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ion_buffer_destroy(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;
	struct ion_device *dev = buffer->dev;

	mutex_lock(&dev->buffer_lock);
	rb_erase(&buffer->node, &dev->buffers);
	mutex_unlock(&dev->buffer_lock);

	if (heap->flags & ION_HEAP_FLAG_DEFER_FREE)
		ion_heap_freelist_add(heap, buffer);
	else
		ion_buffer_destroy(buffer);
}