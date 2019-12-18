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
typedef  scalar_t__ UInt32 ;
typedef  int Byte ;

/* Variables and functions */
 int kNumLogBits ; 

void LzmaEnc_FastPosInit(Byte *g_FastPos)
{
  int c = 2, slotFast;
  g_FastPos[0] = 0;
  g_FastPos[1] = 1;
  
  for (slotFast = 2; slotFast < kNumLogBits * 2; slotFast++)
  {
    UInt32 k = (1 << ((slotFast >> 1) - 1));
    UInt32 j;
    for (j = 0; j < k; j++, c++)
      g_FastPos[c] = (Byte)slotFast;
  }
}