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
typedef  int USHORT ;
typedef  int ULONG ;

/* Variables and functions */

__attribute__((used)) static
inline
USHORT
NextLFSR(USHORT Lfsr, USHORT InputBit)
{
  ULONG NextLfsr = Lfsr >> 1;

  NextLfsr |= (((Lfsr ^ NextLfsr) ^ InputBit)) << 7;

  return NextLfsr;
}