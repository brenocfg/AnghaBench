#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* methods; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* free_p ) (TYPE_2__*,void*) ;} ;
typedef  TYPE_2__* MemoryContext ;

/* Variables and functions */
 TYPE_2__* GetMemoryChunkContext (void*) ; 
 int /*<<< orphan*/  VALGRIND_MEMPOOL_FREE (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*) ; 

void
pfree(void *pointer)
{
	MemoryContext context = GetMemoryChunkContext(pointer);

	context->methods->free_p(context, pointer);
	VALGRIND_MEMPOOL_FREE(context, pointer);
}