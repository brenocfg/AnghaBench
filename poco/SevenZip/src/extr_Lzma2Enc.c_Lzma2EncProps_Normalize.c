#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt64 ;
typedef  int UInt32 ;
struct TYPE_5__ {int numThreads; int dictSize; } ;
struct TYPE_6__ {int numBlockThreads; int numTotalThreads; scalar_t__ blockSize; TYPE_1__ lzmaProps; } ;
typedef  TYPE_1__ CLzmaEncProps ;
typedef  TYPE_2__ CLzma2EncProps ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEncProps_Normalize (TYPE_1__*) ; 
 int NUM_MT_CODER_THREADS_MAX ; 

void Lzma2EncProps_Normalize(CLzma2EncProps *p)
{
  int t1, t1n, t2, t3;
  {
    CLzmaEncProps lzmaProps = p->lzmaProps;
    LzmaEncProps_Normalize(&lzmaProps);
    t1n = lzmaProps.numThreads;
  }

  t1 = p->lzmaProps.numThreads;
  t2 = p->numBlockThreads;
  t3 = p->numTotalThreads;

  if (t2 > NUM_MT_CODER_THREADS_MAX)
    t2 = NUM_MT_CODER_THREADS_MAX;

  if (t3 <= 0)
  {
    if (t2 <= 0)
      t2 = 1;
    t3 = t1n * t2;
  }
  else if (t2 <= 0)
  {
    t2 = t3 / t1n;
    if (t2 == 0)
    {
      t1 = 1;
      t2 = t3;
    }
    if (t2 > NUM_MT_CODER_THREADS_MAX)
      t2 = NUM_MT_CODER_THREADS_MAX;
  }
  else if (t1 <= 0)
  {
    t1 = t3 / t2;
    if (t1 == 0)
      t1 = 1;
  }
  else
    t3 = t1n * t2;

  p->lzmaProps.numThreads = t1;
  p->numBlockThreads = t2;
  p->numTotalThreads = t3;
  LzmaEncProps_Normalize(&p->lzmaProps);

  if (p->blockSize == 0)
  {
    UInt32 dictSize = p->lzmaProps.dictSize;
    UInt64 blockSize = (UInt64)dictSize << 2;
    const UInt32 kMinSize = (UInt32)1 << 20;
    const UInt32 kMaxSize = (UInt32)1 << 28;
    if (blockSize < kMinSize) blockSize = kMinSize;
    if (blockSize > kMaxSize) blockSize = kMaxSize;
    if (blockSize < dictSize) blockSize = dictSize;
    p->blockSize = (size_t)blockSize;
  }
}