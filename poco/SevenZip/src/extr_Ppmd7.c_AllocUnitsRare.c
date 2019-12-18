#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_6__ {scalar_t__ GlueCount; scalar_t__* FreeList; void* UnitsStart; void* Text; } ;
typedef  TYPE_1__ CPpmd7 ;

/* Variables and functions */
 int /*<<< orphan*/  GlueFreeBlocks (TYPE_1__*) ; 
 int /*<<< orphan*/  I2U (unsigned int) ; 
 unsigned int PPMD_NUM_INDEXES ; 
 void* RemoveNode (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  SplitBlock (TYPE_1__*,void*,unsigned int,unsigned int) ; 
 scalar_t__ U2B (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *AllocUnitsRare(CPpmd7 *p, unsigned indx)
{
  unsigned i;
  void *retVal;
  if (p->GlueCount == 0)
  {
    GlueFreeBlocks(p);
    if (p->FreeList[indx] != 0)
      return RemoveNode(p, indx);
  }
  i = indx;
  do
  {
    if (++i == PPMD_NUM_INDEXES)
    {
      UInt32 numBytes = U2B(I2U(indx));
      p->GlueCount--;
      return ((UInt32)(p->UnitsStart - p->Text) > numBytes) ? (p->UnitsStart -= numBytes) : (NULL);
    }
  }
  while (p->FreeList[i] == 0);
  retVal = RemoveNode(p, i);
  SplitBlock(p, retVal, i, indx);
  return retVal;
}