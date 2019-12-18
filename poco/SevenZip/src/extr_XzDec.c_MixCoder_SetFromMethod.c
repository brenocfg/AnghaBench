#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_3__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/ * ids; int /*<<< orphan*/ * coders; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  IStateCoder ;
typedef  TYPE_1__ CMixCoder ;

/* Variables and functions */
 int /*<<< orphan*/  BraState_SetFromMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lzma2State_SetFromMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SbState_SetFromMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  XZ_ID_LZMA2 129 
#define  XZ_ID_Subblock 128 

SRes MixCoder_SetFromMethod(CMixCoder *p, int coderIndex, UInt64 methodId)
{
  IStateCoder *sc = &p->coders[coderIndex];
  p->ids[coderIndex] = methodId;
  switch(methodId)
  {
    case XZ_ID_LZMA2: return Lzma2State_SetFromMethod(sc, p->alloc);
    #ifdef USE_SUBBLOCK
    case XZ_ID_Subblock: return SbState_SetFromMethod(sc, p->alloc);
    #endif
  }
  if (coderIndex == 0)
    return SZ_ERROR_UNSUPPORTED;
  return BraState_SetFromMethod(sc, methodId, 0, p->alloc);
}