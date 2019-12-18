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
typedef  int /*<<< orphan*/  CPpmd7z_RangeEnc ;

/* Variables and functions */
 int /*<<< orphan*/  RangeEnc_ShiftLow (int /*<<< orphan*/ *) ; 

void Ppmd7z_RangeEnc_FlushData(CPpmd7z_RangeEnc *p)
{
  unsigned i;
  for (i = 0; i < 5; i++)
    RangeEnc_ShiftLow(p);
}