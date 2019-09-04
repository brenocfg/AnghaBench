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
typedef  int /*<<< orphan*/  zend_mm_heap ;

/* Variables and functions */
 int /*<<< orphan*/  zend_mm_munmap (void*,size_t) ; 

__attribute__((used)) static void zend_mm_chunk_free(zend_mm_heap *heap, void *addr, size_t size)
{
#if ZEND_MM_STORAGE
	if (UNEXPECTED(heap->storage)) {
		heap->storage->handlers.chunk_free(heap->storage, addr, size);
		return;
	}
#endif
	zend_mm_munmap(addr, size);
}