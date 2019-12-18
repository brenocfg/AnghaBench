#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ dicSize; } ;
struct TYPE_17__ {scalar_t__ dicBufSize; TYPE_2__ prop; int /*<<< orphan*/ * dic; } ;
struct TYPE_15__ {scalar_t__ (* Alloc ) (TYPE_1__*,scalar_t__) ;} ;
typedef  scalar_t__ SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CLzmaProps ;
typedef  TYPE_3__ CLzmaDec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaDec_AllocateProbs2 (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LzmaDec_FreeDict (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LzmaDec_FreeProbs (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LzmaProps_Decode (TYPE_2__*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__) ; 

SRes LzmaDec_Allocate(CLzmaDec *p, const Byte *props, unsigned propsSize, ISzAlloc *alloc)
{
  CLzmaProps propNew;
  SizeT dicBufSize;
  RINOK(LzmaProps_Decode(&propNew, props, propsSize));
  RINOK(LzmaDec_AllocateProbs2(p, &propNew, alloc));
  dicBufSize = propNew.dicSize;
  if (p->dic == 0 || dicBufSize != p->dicBufSize)
  {
    LzmaDec_FreeDict(p, alloc);
    p->dic = (Byte *)alloc->Alloc(alloc, dicBufSize);
    if (p->dic == 0)
    {
      LzmaDec_FreeProbs(p, alloc);
      return SZ_ERROR_MEM;
    }
  }
  p->dicBufSize = dicBufSize;
  p->prop = propNew;
  return SZ_OK;
}