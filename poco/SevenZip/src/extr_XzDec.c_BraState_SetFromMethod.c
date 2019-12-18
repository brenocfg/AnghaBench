#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_10__ {int encodeMode; scalar_t__ methodId; } ;
struct TYPE_9__ {int /*<<< orphan*/  Code; int /*<<< orphan*/  Init; int /*<<< orphan*/  SetProps; int /*<<< orphan*/  Free; TYPE_3__* p; } ;
struct TYPE_8__ {TYPE_3__* (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ IStateCoder ;
typedef  TYPE_3__ CBraState ;

/* Variables and functions */
 int /*<<< orphan*/  BraState_Code ; 
 int /*<<< orphan*/  BraState_Free ; 
 int /*<<< orphan*/  BraState_Init ; 
 int /*<<< orphan*/  BraState_SetProps ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ XZ_ID_ARM ; 
 scalar_t__ XZ_ID_ARMT ; 
 scalar_t__ XZ_ID_Delta ; 
 scalar_t__ XZ_ID_IA64 ; 
 scalar_t__ XZ_ID_PPC ; 
 scalar_t__ XZ_ID_SPARC ; 
 scalar_t__ XZ_ID_X86 ; 
 TYPE_3__* stub1 (TYPE_1__*,int) ; 

SRes BraState_SetFromMethod(IStateCoder *p, UInt64 id, int encodeMode, ISzAlloc *alloc)
{
  CBraState *decoder;
  if (id != XZ_ID_Delta &&
      id != XZ_ID_X86 &&
      id != XZ_ID_PPC &&
      id != XZ_ID_IA64 &&
      id != XZ_ID_ARM &&
      id != XZ_ID_ARMT &&
      id != XZ_ID_SPARC)
    return SZ_ERROR_UNSUPPORTED;
  p->p = 0;
  decoder = alloc->Alloc(alloc, sizeof(CBraState));
  if (decoder == 0)
    return SZ_ERROR_MEM;
  decoder->methodId = (UInt32)id;
  decoder->encodeMode = encodeMode;
  p->p = decoder;
  p->Free = BraState_Free;
  p->SetProps = BraState_SetProps;
  p->Init = BraState_Init;
  p->Code = BraState_Code;
  return SZ_OK;
}