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
struct TYPE_6__ {int (* chunk_extend ) (TYPE_4__*,void*,size_t,size_t) ;} ;
struct TYPE_8__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 scalar_t__ UNEXPECTED (TYPE_4__*) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 void* mremap (void*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,void*,size_t,size_t) ; 
 int /*<<< orphan*/ * zend_mm_mmap_fixed (char*,size_t) ; 

__attribute__((used)) static int zend_mm_chunk_extend(zend_mm_heap *heap, void *addr, size_t old_size, size_t new_size)
{
#if ZEND_MM_STORAGE
	if (UNEXPECTED(heap->storage)) {
		if (heap->storage->handlers.chunk_extend) {
			return heap->storage->handlers.chunk_extend(heap->storage, addr, old_size, new_size);
		} else {
			return 0;
		}
	}
#endif
#ifdef HAVE_MREMAP
	/* We don't use MREMAP_MAYMOVE due to alignment requirements. */
	void *ptr = mremap(addr, old_size, new_size, 0);
	if (ptr == MAP_FAILED) {
		return 0;
	}
	/* Sanity check: The mapping shouldn't have moved. */
	ZEND_ASSERT(ptr == addr);
	return 1;
#elif !defined(_WIN32)
	return (zend_mm_mmap_fixed((char*)addr + old_size, new_size - old_size) != NULL);
#else
	return 0;
#endif
}