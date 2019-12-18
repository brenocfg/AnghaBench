#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_7__ {int pb; int lc; int lp; } ;
struct TYPE_8__ {int dicPos; TYPE_1__ prop; } ;
struct TYPE_9__ {int state; int control; int unpackSize; int packSize; int /*<<< orphan*/  needInitProp; TYPE_2__ decoder; } ;
typedef  int ELzma2State ;
typedef  TYPE_3__ CLzma2Dec ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  LZMA2_GET_LZMA_MODE (TYPE_3__*) ; 
 int /*<<< orphan*/  LZMA2_IS_THERE_PROP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZMA2_IS_UNCOMPRESSED_STATE (TYPE_3__*) ; 
 int LZMA2_LCLP_MAX ; 
#define  LZMA2_STATE_CONTROL 133 
 int LZMA2_STATE_DATA ; 
 int LZMA2_STATE_ERROR ; 
 int LZMA2_STATE_FINISHED ; 
#define  LZMA2_STATE_PACK0 132 
#define  LZMA2_STATE_PACK1 131 
#define  LZMA2_STATE_PROP 130 
#define  LZMA2_STATE_UNPACK0 129 
#define  LZMA2_STATE_UNPACK1 128 
 int /*<<< orphan*/  PRF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static ELzma2State Lzma2Dec_UpdateState(CLzma2Dec *p, Byte b)
{
  switch(p->state)
  {
    case LZMA2_STATE_CONTROL:
      p->control = b;
      PRF(printf("\n %4X ", p->decoder.dicPos));
      PRF(printf(" %2X", b));
      if (p->control == 0)
        return LZMA2_STATE_FINISHED;
      if (LZMA2_IS_UNCOMPRESSED_STATE(p))
      {
        if ((p->control & 0x7F) > 2)
          return LZMA2_STATE_ERROR;
        p->unpackSize = 0;
      }
      else
        p->unpackSize = (UInt32)(p->control & 0x1F) << 16;
      return LZMA2_STATE_UNPACK0;
    
    case LZMA2_STATE_UNPACK0:
      p->unpackSize |= (UInt32)b << 8;
      return LZMA2_STATE_UNPACK1;
    
    case LZMA2_STATE_UNPACK1:
      p->unpackSize |= (UInt32)b;
      p->unpackSize++;
      PRF(printf(" %8d", p->unpackSize));
      return (LZMA2_IS_UNCOMPRESSED_STATE(p)) ? LZMA2_STATE_DATA : LZMA2_STATE_PACK0;
    
    case LZMA2_STATE_PACK0:
      p->packSize = (UInt32)b << 8;
      return LZMA2_STATE_PACK1;

    case LZMA2_STATE_PACK1:
      p->packSize |= (UInt32)b;
      p->packSize++;
      PRF(printf(" %8d", p->packSize));
      return LZMA2_IS_THERE_PROP(LZMA2_GET_LZMA_MODE(p)) ? LZMA2_STATE_PROP:
        (p->needInitProp ? LZMA2_STATE_ERROR : LZMA2_STATE_DATA);

    case LZMA2_STATE_PROP:
    {
      int lc, lp;
      if (b >= (9 * 5 * 5))
        return LZMA2_STATE_ERROR;
      lc = b % 9;
      b /= 9;
      p->decoder.prop.pb = b / 5;
      lp = b % 5;
      if (lc + lp > LZMA2_LCLP_MAX)
        return LZMA2_STATE_ERROR;
      p->decoder.prop.lc = lc;
      p->decoder.prop.lp = lp;
      p->needInitProp = False;
      return LZMA2_STATE_DATA;
    }
  }
  return LZMA2_STATE_ERROR;
}