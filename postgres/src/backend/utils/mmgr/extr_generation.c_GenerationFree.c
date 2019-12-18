#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ nfree; scalar_t__ nchunks; scalar_t__ blksize; int /*<<< orphan*/  node; } ;
struct TYPE_12__ {scalar_t__ requested_size; scalar_t__ size; int /*<<< orphan*/ * context; TYPE_4__* block; } ;
struct TYPE_11__ {TYPE_4__* block; } ;
struct TYPE_10__ {int /*<<< orphan*/  mem_allocated; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* MemoryContext ;
typedef  TYPE_2__ GenerationContext ;
typedef  TYPE_3__ GenerationChunk ;
typedef  TYPE_4__ GenerationBlock ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GENERATIONCHUNK_PRIVATE_LEN ; 
 TYPE_3__* GenerationPointerGetChunk (void*) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  sentinel_ok (void*,scalar_t__) ; 
 int /*<<< orphan*/  wipe_mem (void*,scalar_t__) ; 

__attribute__((used)) static void
GenerationFree(MemoryContext context, void *pointer)
{
	GenerationContext *set = (GenerationContext *) context;
	GenerationChunk *chunk = GenerationPointerGetChunk(pointer);
	GenerationBlock *block;

	/* Allow access to private part of chunk header. */
	VALGRIND_MAKE_MEM_DEFINED(chunk, GENERATIONCHUNK_PRIVATE_LEN);

	block = chunk->block;

#ifdef MEMORY_CONTEXT_CHECKING
	/* Test for someone scribbling on unused space in chunk */
	if (chunk->requested_size < chunk->size)
		if (!sentinel_ok(pointer, chunk->requested_size))
			elog(WARNING, "detected write past chunk end in %s %p",
				 ((MemoryContext) set)->name, chunk);
#endif

#ifdef CLOBBER_FREED_MEMORY
	wipe_mem(pointer, chunk->size);
#endif

	/* Reset context to NULL in freed chunks */
	chunk->context = NULL;

#ifdef MEMORY_CONTEXT_CHECKING
	/* Reset requested_size to 0 in freed chunks */
	chunk->requested_size = 0;
#endif

	block->nfree += 1;

	Assert(block->nchunks > 0);
	Assert(block->nfree <= block->nchunks);

	/* If there are still allocated chunks in the block, we're done. */
	if (block->nfree < block->nchunks)
		return;

	/*
	 * The block is empty, so let's get rid of it. First remove it from the
	 * list of blocks, then return it to malloc().
	 */
	dlist_delete(&block->node);

	/* Also make sure the block is not marked as the current block. */
	if (set->block == block)
		set->block = NULL;

	context->mem_allocated -= block->blksize;
	free(block);
}