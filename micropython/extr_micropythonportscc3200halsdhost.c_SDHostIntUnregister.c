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

/* Variables and functions */
 int /*<<< orphan*/  INT_MMCHS ; 
 int /*<<< orphan*/  IntDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntUnregister (int /*<<< orphan*/ ) ; 

void
SDHostIntUnregister(unsigned long ulBase)
{
  //
  // Disable the SDHost interrupt.
  //
  IntDisable(INT_MMCHS);

  //
  // Unregister the interrupt handler.
  //
  IntUnregister(INT_MMCHS);
}