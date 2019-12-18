#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt32 ;
struct TYPE_6__ {int /*<<< orphan*/  p; } ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;
struct TYPE_7__ {int lp; int lc; int pbMask; int pb; int lpMask; scalar_t__ additionalOffset; scalar_t__ optimumCurrentIndex; scalar_t__ optimumEndIndex; void** posAlignEncoder; TYPE_2__ repLenEnc; TYPE_1__ lenEnc; void** posEncoders; void*** posSlotEncoder; void** litProbs; void** isRepG2; void** isRepG1; void** isRepG0; void** isRep; void*** isRep0Long; void*** isMatch; int /*<<< orphan*/  rc; scalar_t__* reps; scalar_t__ state; } ;
typedef  void* CLzmaProb ;
typedef  TYPE_3__ CLzmaEnc ;

/* Variables and functions */
 size_t LZMA_NUM_PB_STATES_MAX ; 
 size_t LZMA_NUM_REPS ; 
 int /*<<< orphan*/  LenEnc_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RangeEnc_Init (int /*<<< orphan*/ *) ; 
 size_t kEndPosModelIndex ; 
 int kNumAlignBits ; 
 size_t kNumFullDistances ; 
 size_t kNumLenToPosStates ; 
 int kNumPosSlotBits ; 
 size_t kNumStates ; 
 void* kProbInitValue ; 

void LzmaEnc_Init(CLzmaEnc *p)
{
  UInt32 i;
  p->state = 0;
  for (i = 0 ; i < LZMA_NUM_REPS; i++)
    p->reps[i] = 0;

  RangeEnc_Init(&p->rc);


  for (i = 0; i < kNumStates; i++)
  {
    UInt32 j;
    for (j = 0; j < LZMA_NUM_PB_STATES_MAX; j++)
    {
      p->isMatch[i][j] = kProbInitValue;
      p->isRep0Long[i][j] = kProbInitValue;
    }
    p->isRep[i] = kProbInitValue;
    p->isRepG0[i] = kProbInitValue;
    p->isRepG1[i] = kProbInitValue;
    p->isRepG2[i] = kProbInitValue;
  }

  {
    UInt32 num = 0x300 << (p->lp + p->lc);
    for (i = 0; i < num; i++)
      p->litProbs[i] = kProbInitValue;
  }

  {
    for (i = 0; i < kNumLenToPosStates; i++)
    {
      CLzmaProb *probs = p->posSlotEncoder[i];
      UInt32 j;
      for (j = 0; j < (1 << kNumPosSlotBits); j++)
        probs[j] = kProbInitValue;
    }
  }
  {
    for (i = 0; i < kNumFullDistances - kEndPosModelIndex; i++)
      p->posEncoders[i] = kProbInitValue;
  }

  LenEnc_Init(&p->lenEnc.p);
  LenEnc_Init(&p->repLenEnc.p);

  for (i = 0; i < (1 << kNumAlignBits); i++)
    p->posAlignEncoder[i] = kProbInitValue;

  p->optimumEndIndex = 0;
  p->optimumCurrentIndex = 0;
  p->additionalOffset = 0;

  p->pbMask = (1 << p->pb) - 1;
  p->lpMask = (1 << p->lp) - 1;
}