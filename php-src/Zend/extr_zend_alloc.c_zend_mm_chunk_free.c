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
struct TYPE_6__ {int /*<<< orphan*/  (* chunk_free ) (TYPE_4__*,void*,size_t) ;} ;
struct TYPE_8__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,void*,size_t) ; 
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