#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int numCoders; scalar_t__* ids; int /*<<< orphan*/  alloc; TYPE_1__* coders; } ;
struct TYPE_13__ {TYPE_2__* filters; } ;
struct TYPE_12__ {scalar_t__ id; int /*<<< orphan*/  propsSize; int /*<<< orphan*/  props; } ;
struct TYPE_11__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* SetProps ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ IStateCoder ;
typedef  TYPE_2__ CXzFilter ;
typedef  TYPE_3__ CXzBlock ;
typedef  TYPE_4__ CMixCoder ;
typedef  int Bool ;

/* Variables and functions */
 int /*<<< orphan*/  MixCoder_Free (TYPE_4__*) ; 
 int /*<<< orphan*/  MixCoder_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  MixCoder_SetFromMethod (TYPE_4__*,int,scalar_t__) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int True ; 
 int XzBlock_GetNumFilters (TYPE_3__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SRes XzDec_Init(CMixCoder *p, const CXzBlock *block)
{
  int i;
  Bool needReInit = True;
  int numFilters = XzBlock_GetNumFilters(block);
  if (numFilters == p->numCoders)
  {
    for (i = 0; i < numFilters; i++)
      if (p->ids[i] != block->filters[numFilters - 1 - i].id)
        break;
    needReInit = (i != numFilters);
  }
  if (needReInit)
  {
    MixCoder_Free(p);
    p->numCoders = numFilters;
    for (i = 0; i < numFilters; i++)
    {
      const CXzFilter *f = &block->filters[numFilters - 1 - i];
      RINOK(MixCoder_SetFromMethod(p, i, f->id));
    }
  }
  for (i = 0; i < numFilters; i++)
  {
    const CXzFilter *f = &block->filters[numFilters - 1 - i];
    IStateCoder *sc = &p->coders[i];
    RINOK(sc->SetProps(sc->p, f->props, f->propsSize, p->alloc));
  }
  MixCoder_Init(p);
  return SZ_OK;
}