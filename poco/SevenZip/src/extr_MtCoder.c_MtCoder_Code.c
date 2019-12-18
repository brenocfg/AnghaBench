#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* param; int /*<<< orphan*/  func; int /*<<< orphan*/  thread; } ;
struct TYPE_11__ {unsigned int numThreads; scalar_t__ res; TYPE_1__* threads; int /*<<< orphan*/  progress; int /*<<< orphan*/  mtProgress; } ;
struct TYPE_10__ {TYPE_3__ thread; int /*<<< orphan*/  canRead; int /*<<< orphan*/  canWrite; int /*<<< orphan*/  stopReading; } ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ CMtThread ;
typedef  TYPE_2__ CMtCoder ;
typedef  TYPE_3__ CLoopThread ;

/* Variables and functions */
 int /*<<< orphan*/  CMtThread_CloseEvents (TYPE_1__*) ; 
 int /*<<< orphan*/  CMtThread_Prepare (TYPE_1__*) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 scalar_t__ LoopThread_Create (TYPE_3__*) ; 
 scalar_t__ LoopThread_StartSubThread (TYPE_3__*) ; 
 int /*<<< orphan*/  LoopThread_WaitSubThread (TYPE_3__*) ; 
 int /*<<< orphan*/  MtProgress_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_THREAD ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  ThreadFunc ; 
 int /*<<< orphan*/  Thread_WasCreated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  True ; 

SRes MtCoder_Code(CMtCoder *p)
{
  unsigned i, numThreads = p->numThreads;
  SRes res = SZ_OK;
  p->res = SZ_OK;

  MtProgress_Init(&p->mtProgress, p->progress);

  for (i = 0; i < numThreads; i++)
  {
    RINOK(CMtThread_Prepare(&p->threads[i]));
  }

  for (i = 0; i < numThreads; i++)
  {
    CMtThread *t = &p->threads[i];
    CLoopThread *lt = &t->thread;

    if (!Thread_WasCreated(&lt->thread))
    {
      lt->func = ThreadFunc;
      lt->param = t;

      if (LoopThread_Create(lt) != SZ_OK)
      {
        res = SZ_ERROR_THREAD;
        break;
      }
    }
  }

  if (res == SZ_OK)
  {
    unsigned j;
    for (i = 0; i < numThreads; i++)
    {
      CMtThread *t = &p->threads[i];
      if (LoopThread_StartSubThread(&t->thread) != SZ_OK)
      {
        res = SZ_ERROR_THREAD;
        p->threads[0].stopReading = True;
        break;
      }
    }

    Event_Set(&p->threads[0].canWrite);
    Event_Set(&p->threads[0].canRead);

    for (j = 0; j < i; j++)
      LoopThread_WaitSubThread(&p->threads[j].thread);
  }

  for (i = 0; i < numThreads; i++)
    CMtThread_CloseEvents(&p->threads[i]);
  return (res == SZ_OK) ? p->res : res;
}