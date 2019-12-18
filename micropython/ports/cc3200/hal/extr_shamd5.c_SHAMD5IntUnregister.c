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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INT_SHA ; 
 int /*<<< orphan*/  IntDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntUnregister (int /*<<< orphan*/ ) ; 
 scalar_t__ SHAMD5_BASE ; 

void
SHAMD5IntUnregister(uint32_t ui32Base)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == SHAMD5_BASE);

    //
    // Disable the interrupt.
    //
    IntDisable(INT_SHA);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_SHA);
}