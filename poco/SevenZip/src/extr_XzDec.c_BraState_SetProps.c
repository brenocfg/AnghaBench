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
typedef  int UInt32 ;
struct TYPE_2__ {int ip; int methodId; unsigned int delta; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CBraState ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int GetUi32 (scalar_t__ const*) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
#define  XZ_ID_ARM 132 
#define  XZ_ID_ARMT 131 
 int XZ_ID_Delta ; 
#define  XZ_ID_IA64 130 
#define  XZ_ID_PPC 129 
#define  XZ_ID_SPARC 128 

SRes BraState_SetProps(void *pp, const Byte *props, size_t propSize, ISzAlloc *alloc)
{
  CBraState *p = ((CBraState *)pp);
  alloc = alloc;
  p->ip = 0;
  if (p->methodId == XZ_ID_Delta)
  {
    if (propSize != 1)
      return SZ_ERROR_UNSUPPORTED;
    p->delta = (unsigned)props[0] + 1;
  }
  else
  {
    if (propSize == 4)
    {
      UInt32 v = GetUi32(props);
      switch(p->methodId)
      {
        case XZ_ID_PPC:
        case XZ_ID_ARM:
        case XZ_ID_SPARC:
          if ((v & 3) != 0)
            return SZ_ERROR_UNSUPPORTED;
          break;
        case XZ_ID_ARMT:
          if ((v & 1) != 0)
            return SZ_ERROR_UNSUPPORTED;
          break;
        case XZ_ID_IA64:
          if ((v & 0xF) != 0)
            return SZ_ERROR_UNSUPPORTED;
          break;
      }
      p->ip = v;
    }
    else if (propSize != 0)
      return SZ_ERROR_UNSUPPORTED;
  }
  return SZ_OK;
}