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
struct TYPE_3__ {int /*<<< orphan*/  res; int /*<<< orphan*/ * progress; scalar_t__ totalOutSize; scalar_t__ totalInSize; scalar_t__* outSizes; scalar_t__* inSizes; } ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  TYPE_1__ CMtProgress ;

/* Variables and functions */
 unsigned int NUM_MT_CODER_THREADS_MAX ; 
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static void MtProgress_Init(CMtProgress *p, ICompressProgress *progress)
{
  unsigned i;
  for (i = 0; i < NUM_MT_CODER_THREADS_MAX; i++)
    p->inSizes[i] = p->outSizes[i] = 0;
  p->totalInSize = p->totalOutSize = 0;
  p->progress = progress;
  p->res = SZ_OK;
}