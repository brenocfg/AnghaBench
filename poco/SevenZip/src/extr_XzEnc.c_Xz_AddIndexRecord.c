#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* UInt64 ;
struct TYPE_14__ {void* unpackSize; void* totalSize; } ;
struct TYPE_13__ {int numBlocksAllocated; int numBlocks; TYPE_3__* blocks; } ;
struct TYPE_12__ {TYPE_3__* (* Alloc ) (TYPE_1__*,size_t) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CXzStream ;
typedef  TYPE_3__ CXzBlockSizes ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  Xz_Free (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* stub1 (TYPE_1__*,size_t) ; 

SRes Xz_AddIndexRecord(CXzStream *p, UInt64 unpackSize, UInt64 totalSize, ISzAlloc *alloc)
{
  if (p->blocks == 0 || p->numBlocksAllocated == p->numBlocks)
  {
    size_t num = (p->numBlocks + 1) * 2;
    size_t newSize = sizeof(CXzBlockSizes) * num;
    CXzBlockSizes *blocks;
    if (newSize / sizeof(CXzBlockSizes) != num)
      return SZ_ERROR_MEM;
    blocks = alloc->Alloc(alloc, newSize);
    if (blocks == 0)
      return SZ_ERROR_MEM;
    if (p->numBlocks != 0)
    {
      memcpy(blocks, p->blocks, p->numBlocks * sizeof(CXzBlockSizes));
      Xz_Free(p, alloc);
    }
    p->blocks = blocks;
    p->numBlocksAllocated = num;
  }
  {
    CXzBlockSizes *block = &p->blocks[p->numBlocks++];
    block->totalSize = totalSize;
    block->unpackSize = unpackSize;
  }
  return SZ_OK;
}