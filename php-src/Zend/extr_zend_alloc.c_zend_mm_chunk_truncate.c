#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* storage; } ;
typedef  TYPE_2__ zend_mm_heap ;
struct TYPE_6__ {int (* chunk_truncate ) (TYPE_4__*,void*,size_t,size_t) ;} ;
struct TYPE_8__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (TYPE_4__*) ; 
 int stub1 (TYPE_4__*,void*,size_t,size_t) ; 
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