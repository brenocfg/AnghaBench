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
typedef  scalar_t__ UInt64 ;
typedef  size_t UInt32 ;

/* Variables and functions */

__attribute__((used)) static UInt64 GetSum(const UInt64 *values, UInt32 index)
{
  UInt64 sum = 0;
  UInt32 i;
  for (i = 0; i < index; i++)
    sum += values[i];
  return sum;
}