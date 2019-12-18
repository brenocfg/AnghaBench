#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stats_string ;
struct TYPE_9__ {char* endptr; char* freeptr; struct TYPE_9__* next; } ;
struct TYPE_8__ {int size; scalar_t__ aset; } ;
struct TYPE_7__ {TYPE_3__** freelist; TYPE_4__* blocks; } ;
struct TYPE_6__ {int /*<<< orphan*/  freespace; int /*<<< orphan*/  totalspace; int /*<<< orphan*/  freechunks; int /*<<< orphan*/  nblocks; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  (* MemoryStatsPrintFunc ) (int /*<<< orphan*/ ,void*,char*) ;
typedef  TYPE_1__ MemoryContextCounters ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  AllocSetContext ;
typedef  TYPE_2__* AllocSet ;
typedef  TYPE_3__* AllocChunk ;
typedef  TYPE_4__* AllocBlock ;

/* Variables and functions */
 int ALLOCSET_NUM_FREELISTS ; 
 int ALLOC_CHUNKHDRSZ ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int) ; 

__attribute__((used)) static void
AllocSetStats(MemoryContext context,
			  MemoryStatsPrintFunc printfunc, void *passthru,
			  MemoryContextCounters *totals)
{
	AllocSet	set = (AllocSet) context;
	Size		nblocks = 0;
	Size		freechunks = 0;
	Size		totalspace;
	Size		freespace = 0;
	AllocBlock	block;
	int			fidx;

	/* Include context header in totalspace */
	totalspace = MAXALIGN(sizeof(AllocSetContext));

	for (block = set->blocks; block != NULL; block = block->next)
	{
		nblocks++;
		totalspace += block->endptr - ((char *) block);
		freespace += block->endptr - block->freeptr;
	}
	for (fidx = 0; fidx < ALLOCSET_NUM_FREELISTS; fidx++)
	{
		AllocChunk	chunk;

		for (chunk = set->freelist[fidx]; chunk != NULL;
			 chunk = (AllocChunk) chunk->aset)
		{
			freechunks++;
			freespace += chunk->size + ALLOC_CHUNKHDRSZ;
		}
	}

	if (printfunc)
	{
		char		stats_string[200];

		snprintf(stats_string, sizeof(stats_string),
				 "%zu total in %zd blocks; %zu free (%zd chunks); %zu used",
				 totalspace, nblocks, freespace, freechunks,
				 totalspace - freespace);
		printfunc(context, passthru, stats_string);
	}

	if (totals)
	{
		totals->nblocks += nblocks;
		totals->freechunks += freechunks;
		totals->totalspace += totalspace;
		totals->freespace += freespace;
	}
}