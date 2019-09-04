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
 int /*<<< orphan*/  zend_mm_munmap (char*,size_t) ; 

__attribute__((used)) static int zend_mm_chunk_truncate(zend_mm_heap *heap, void *addr, size_t old_size, size_t new_size)
{
#if ZEND_MM_STORAGE
	if (UNEXPECTED(heap->storage)) {
		if (heap->storage->handlers.chunk_truncate) {
			return heap->storage->handlers.chunk_truncate(heap->storage, addr, old_size, new_size);
		} else {
			return 0;
		}
	}
#endif
#ifndef _WIN32
	zend_mm_munmap((char*)addr + new_size, old_size - new_size);
	return 1;
#else
	return 0;
#endif
}