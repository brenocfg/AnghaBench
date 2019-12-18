#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int blockSize; int /*<<< orphan*/  blocks; int /*<<< orphan*/ * block; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ GenerationContext ;

/* Variables and functions */
 int /*<<< orphan*/  AllocHugeSizeIsValid (int) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GenerationChunk ; 
 int /*<<< orphan*/  GenerationMethods ; 
 scalar_t__ Generation_CHUNKHDRSZ ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MemoryContextCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  MemoryContextStats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 
 int /*<<< orphan*/  T_GenerationContext ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MemoryContext
GenerationContextCreate(MemoryContext parent,
						const char *name,
						Size blockSize)
{
	GenerationContext *set;

	/* Assert we padded GenerationChunk properly */
	StaticAssertStmt(Generation_CHUNKHDRSZ == MAXALIGN(Generation_CHUNKHDRSZ),
					 "sizeof(GenerationChunk) is not maxaligned");
	StaticAssertStmt(offsetof(GenerationChunk, context) + sizeof(MemoryContext) ==
					 Generation_CHUNKHDRSZ,
					 "padding calculation in GenerationChunk is wrong");

	/*
	 * First, validate allocation parameters.  (If we're going to throw an
	 * error, we should do so before the context is created, not after.)  We
	 * somewhat arbitrarily enforce a minimum 1K block size, mostly because
	 * that's what AllocSet does.
	 */
	if (blockSize != MAXALIGN(blockSize) ||
		blockSize < 1024 ||
		!AllocHugeSizeIsValid(blockSize))
		elog(ERROR, "invalid blockSize for memory context: %zu",
			 blockSize);

	/*
	 * Allocate the context header.  Unlike aset.c, we never try to combine
	 * this with the first regular block, since that would prevent us from
	 * freeing the first generation of allocations.
	 */

	set = (GenerationContext *) malloc(MAXALIGN(sizeof(GenerationContext)));
	if (set == NULL)
	{
		MemoryContextStats(TopMemoryContext);
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory"),
				 errdetail("Failed while creating memory context \"%s\".",
						   name)));
	}

	/*
	 * Avoid writing code that can fail between here and MemoryContextCreate;
	 * we'd leak the header if we ereport in this stretch.
	 */

	/* Fill in GenerationContext-specific header fields */
	set->blockSize = blockSize;
	set->block = NULL;
	dlist_init(&set->blocks);

	/* Finally, do the type-independent part of context creation */
	MemoryContextCreate((MemoryContext) set,
						T_GenerationContext,
						&GenerationMethods,
						parent,
						name);

	return (MemoryContext) set;
}