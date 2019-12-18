#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ GenerationChunk ;

/* Variables and functions */
 int /*<<< orphan*/  GENERATIONCHUNK_PRIVATE_LEN ; 
 TYPE_1__* GenerationPointerGetChunk (void*) ; 
 scalar_t__ Generation_CHUNKHDRSZ ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_NOACCESS (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Size
GenerationGetChunkSpace(MemoryContext context, void *pointer)
{
	GenerationChunk *chunk = GenerationPointerGetChunk(pointer);
	Size		result;

	VALGRIND_MAKE_MEM_DEFINED(chunk, GENERATIONCHUNK_PRIVATE_LEN);
	result = chunk->size + Generation_CHUNKHDRSZ;
	VALGRIND_MAKE_MEM_NOACCESS(chunk, GENERATIONCHUNK_PRIVATE_LEN);
	return result;
}