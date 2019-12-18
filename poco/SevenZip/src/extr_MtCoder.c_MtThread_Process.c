#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* Code ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,size_t,int) ;} ;
struct TYPE_10__ {size_t (* Write ) (TYPE_3__*,int /*<<< orphan*/ ,size_t) ;} ;
struct TYPE_9__ {int stopReading; size_t outBufSize; int /*<<< orphan*/  canWrite; int /*<<< orphan*/  outBuf; TYPE_1__* mtCoder; scalar_t__ stopWriting; int /*<<< orphan*/  index; int /*<<< orphan*/  inBuf; int /*<<< orphan*/  canRead; } ;
struct TYPE_8__ {size_t blockSize; TYPE_3__* outStream; int /*<<< orphan*/  mtProgress; TYPE_4__* mtCallback; int /*<<< orphan*/  inStream; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_2__ CMtThread ;
typedef  int Bool ;

/* Variables and functions */
 scalar_t__ Event_Set (int /*<<< orphan*/ *) ; 
 scalar_t__ Event_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FullRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 TYPE_2__* GET_NEXT_THREAD (TYPE_2__*) ; 
 int /*<<< orphan*/  MtProgress_Reinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SZ_ERROR_THREAD ; 
 int /*<<< orphan*/  SZ_ERROR_WRITE ; 
 int /*<<< orphan*/  SZ_OK ; 
 void* True ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,size_t,int) ; 
 size_t stub2 (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static SRes MtThread_Process(CMtThread *p, Bool *stop)
{
  CMtThread *next;
  *stop = True;
  if (Event_Wait(&p->canRead) != 0)
    return SZ_ERROR_THREAD;
  
  next = GET_NEXT_THREAD(p);
  
  if (p->stopReading)
  {
    next->stopReading = True;
    return Event_Set(&next->canRead) == 0 ? SZ_OK : SZ_ERROR_THREAD;
  }

  {
    size_t size = p->mtCoder->blockSize;
    size_t destSize = p->outBufSize;

    RINOK(FullRead(p->mtCoder->inStream, p->inBuf, &size));
    next->stopReading = *stop = (size != p->mtCoder->blockSize);
    if (Event_Set(&next->canRead) != 0)
      return SZ_ERROR_THREAD;

    RINOK(p->mtCoder->mtCallback->Code(p->mtCoder->mtCallback, p->index,
        p->outBuf, &destSize, p->inBuf, size, *stop));

    MtProgress_Reinit(&p->mtCoder->mtProgress, p->index);

    if (Event_Wait(&p->canWrite) != 0)
      return SZ_ERROR_THREAD;
    if (p->stopWriting)
      return SZ_ERROR_FAIL;
    if (p->mtCoder->outStream->Write(p->mtCoder->outStream, p->outBuf, destSize) != destSize)
      return SZ_ERROR_WRITE;
    return Event_Set(&next->canWrite) == 0 ? SZ_OK : SZ_ERROR_THREAD;
  }
}