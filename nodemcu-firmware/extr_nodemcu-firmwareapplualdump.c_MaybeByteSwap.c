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
struct TYPE_4__ {int little_endian; } ;
struct TYPE_5__ {TYPE_1__ target; } ;
typedef  TYPE_2__ DumpState ;

/* Variables and functions */

__attribute__((used)) static void MaybeByteSwap(char *number, size_t numbersize, DumpState *D)
{
 int x=1;
 int platform_little_endian = *(char*)&x;
 if (platform_little_endian != D->target.little_endian)
 {
  unsigned long i;
  for (i=0; i<numbersize/2; i++)
  {
   char temp = number[i];
   number[i] = number[numbersize-1-i];
   number[numbersize-1-i] = temp;
  }
 }
}