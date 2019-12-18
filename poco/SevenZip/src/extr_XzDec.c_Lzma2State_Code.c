#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  int /*<<< orphan*/  ECoderFinishMode ;
typedef  int /*<<< orphan*/  CLzma2Dec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 int /*<<< orphan*/  Lzma2Dec_DecodeToBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static SRes Lzma2State_Code(void *pp, Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen,
    int srcWasFinished, ECoderFinishMode finishMode, int *wasFinished)
{
  ELzmaStatus status;
  /* ELzmaFinishMode fm = (finishMode == LZMA_FINISH_ANY) ? LZMA_FINISH_ANY : LZMA_FINISH_END; */
  SRes res = Lzma2Dec_DecodeToBuf((CLzma2Dec *)pp, dest, destLen, src, srcLen, finishMode, &status);
  srcWasFinished = srcWasFinished;
  *wasFinished = (status == LZMA_STATUS_FINISHED_WITH_MARK);
  return res;
}