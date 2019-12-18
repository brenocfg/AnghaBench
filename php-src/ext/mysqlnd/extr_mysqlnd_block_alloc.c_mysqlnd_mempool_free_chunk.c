#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* last; TYPE_1__* arena; } ;
struct TYPE_4__ {char* ptr; } ;
typedef  TYPE_2__ MYSQLND_MEMORY_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 

__attribute__((used)) static void
mysqlnd_mempool_free_chunk(MYSQLND_MEMORY_POOL * pool, void * ptr)
{
	DBG_ENTER("mysqlnd_mempool_free_chunk");
	/* Try to back-off and guess if this is the last block allocated */
#ifndef ZEND_TRACK_ARENA_ALLOC
	if (ptr == pool->last) {
		/*
			This was the last allocation. Lucky us, we can free
			a bit of memory from the pool. Next time we will return from the same ptr.
		*/
		pool->arena->ptr = (char*)ptr;
		pool->last = NULL;
	}
#endif
	DBG_VOID_RETURN;
}