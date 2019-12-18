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
typedef  int /*<<< orphan*/ * BusLogic_CommandSizeBuckets_T ;

/* Variables and functions */

__attribute__((used)) static void
BusLogic_IncrementSizeBucket(BusLogic_CommandSizeBuckets_T CommandSizeBuckets,
                             unsigned int Amount)
{
  int Index = 0;
  if (Amount < 8*1024)
  {
    if (Amount < 2*1024)
        Index = (Amount < 1*1024 ? 0 : 1);
    else
        Index = (Amount < 4*1024 ? 2 : 3);
  }
  else if (Amount < 128*1024)
  {
    if (Amount < 32*1024)
        Index = (Amount < 16*1024 ? 4 : 5);
    else
        Index = (Amount < 64*1024 ? 6 : 7);
  }
  else
      Index = (Amount < 256*1024 ? 8 : 9);
  CommandSizeBuckets[Index]++;
}