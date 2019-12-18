#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_5__ {scalar_t__ (* Read ) (TYPE_2__*,int /*<<< orphan*/ *,size_t*) ;} ;
struct TYPE_4__ {int streamEndWasReached; scalar_t__ result; scalar_t__ streamPos; scalar_t__ directInputRem; int pos; int blockSize; scalar_t__ keepSizeAfter; TYPE_2__* stream; int /*<<< orphan*/ * bufferBase; int /*<<< orphan*/ * buffer; scalar_t__ directInput; } ;
typedef  TYPE_1__ CMatchFinder ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ SZ_OK ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static void MatchFinder_ReadBlock(CMatchFinder *p)
{
  if (p->streamEndWasReached || p->result != SZ_OK)
    return;
  if (p->directInput)
  {
    UInt32 curSize = 0xFFFFFFFF - p->streamPos;
    if (curSize > p->directInputRem)
      curSize = (UInt32)p->directInputRem;
    p->directInputRem -= curSize;
    p->streamPos += curSize;
    if (p->directInputRem == 0)
      p->streamEndWasReached = 1;
    return;
  }
  for (;;)
  {
    Byte *dest = p->buffer + (p->streamPos - p->pos);
    size_t size = (p->bufferBase + p->blockSize - dest);
    if (size == 0)
      return;
    p->result = p->stream->Read(p->stream, dest, &size);
    if (p->result != SZ_OK)
      return;
    if (size == 0)
    {
      p->streamEndWasReached = 1;
      return;
    }
    p->streamPos += (UInt32)size;
    if (p->streamPos - p->pos > p->keepSizeAfter)
      return;
  }
}