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
struct TYPE_5__ {char* ptr; scalar_t__ end; } ;
struct TYPE_4__ {void* last; TYPE_2__* arena; } ;
typedef  TYPE_1__ MYSQLND_MEMORY_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (void*) ; 
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 long ZEND_MM_ALIGNED_SIZE (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 void* zend_arena_alloc (TYPE_2__**,size_t) ; 

__attribute__((used)) static void *
mysqlnd_mempool_resize_chunk(MYSQLND_MEMORY_POOL * pool, void * ptr, size_t old_size, size_t size)
{
	DBG_ENTER("mysqlnd_mempool_resize_chunk");

#ifndef ZEND_TRACK_ARENA_ALLOC
	/* Try to back-off and guess if this is the last block allocated */
	if (ptr == pool->last
	  && (ZEND_MM_ALIGNED_SIZE(size) <= ((char*)pool->arena->end - (char*)ptr))) {
		/*
			This was the last allocation. Lucky us, we can free
			a bit of memory from the pool. Next time we will return from the same ptr.
		*/
		pool->arena->ptr = (char*)ptr + ZEND_MM_ALIGNED_SIZE(size);
		DBG_RETURN(ptr);
	}
#endif

	void *new_ptr = zend_arena_alloc(&pool->arena, size);
	memcpy(new_ptr, ptr, MIN(old_size, size));
	pool->last = ptr = new_ptr;
	DBG_RETURN(ptr);
}