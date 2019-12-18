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
struct list {int dummy; } ;
struct TYPE_4__ {size_t block_cnt; int /*<<< orphan*/  mark; scalar_t__ offset; scalar_t__ last_block; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  custom_blocks; } ;
typedef  TYPE_1__ heap_pool_t ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARENA_FREE_FILLER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ WARN_ON (TYPE_1__*) ; 
 int /*<<< orphan*/  block_size (size_t) ; 
 int /*<<< orphan*/  heap_free (struct list*) ; 
 struct list* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (struct list*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void heap_pool_clear(heap_pool_t *heap)
{
    struct list *tmp;

    if(!heap)
        return;

    while((tmp = list_head(&heap->custom_blocks))) {
        list_remove(tmp);
        heap_free(tmp);
    }

    if(WARN_ON(heap)) {
        DWORD i;

        for(i=0; i < heap->block_cnt; i++)
            memset(heap->blocks[i], ARENA_FREE_FILLER, block_size(i));
    }

    heap->last_block = heap->offset = 0;
    heap->mark = FALSE;
}