#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* Read ) (TYPE_3__*,scalar_t__,scalar_t__*) ;} ;
struct TYPE_4__ {scalar_t__ (* Code ) (int /*<<< orphan*/ ,void*,size_t*,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  p; } ;
struct TYPE_5__ {int srcWasFinished; scalar_t__ curPos; scalar_t__ endPos; scalar_t__ buf; TYPE_1__ StateCoder; TYPE_3__* realStream; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  TYPE_2__ CSeqInFilter ;

/* Variables and functions */
 int /*<<< orphan*/  CODER_FINISH_ANY ; 
 scalar_t__ FILTER_BUF_SIZE ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,void*,size_t*,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static SRes SeqInFilter_Read(void *pp, void *data, size_t *size)
{
  CSeqInFilter *p = (CSeqInFilter *)pp;
  size_t sizeOriginal = *size;
  if (sizeOriginal == 0)
    return S_OK;
  *size = 0;
  for (;;)
  {
    if (!p->srcWasFinished && p->curPos == p->endPos)
    {
      p->curPos = 0;
      p->endPos = FILTER_BUF_SIZE;
      RINOK(p->realStream->Read(p->realStream, p->buf, &p->endPos));
      if (p->endPos == 0)
        p->srcWasFinished = 1;
    }
    {
      SizeT srcLen = p->endPos - p->curPos;
      int wasFinished;
      SRes res;
      *size = sizeOriginal;
      res = p->StateCoder.Code(p->StateCoder.p, data, size, p->buf + p->curPos, &srcLen,
        p->srcWasFinished, CODER_FINISH_ANY, &wasFinished);
      p->curPos += srcLen;
      if (*size != 0 || srcLen == 0 || res != 0)
        return res;
    }
  }
}