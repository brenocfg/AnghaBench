#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t last_block; int offset; scalar_t__* blocks; } ;
typedef  TYPE_1__ heap_pool_t ;
typedef  scalar_t__ DWORD ;
typedef  void BYTE ;

/* Variables and functions */
 scalar_t__ block_size (size_t) ; 
 void* heap_pool_alloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 

void *heap_pool_grow(heap_pool_t *heap, void *mem, DWORD size, DWORD inc)
{
    void *ret;

    if(mem == (BYTE*)heap->blocks[heap->last_block] + heap->offset-size
            && heap->offset+inc < block_size(heap->last_block)) {
        heap->offset += inc;
        return mem;
    }

    ret = heap_pool_alloc(heap, size+inc);
    if(ret) /* FIXME: avoid copying for custom blocks */
        memcpy(ret, mem, size);
    return ret;
}