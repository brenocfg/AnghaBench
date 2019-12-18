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
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  B2 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unselect_rows(void)
{
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);
	// make all pins high to select Y7, nothing is connected to that (otherwise the first row will act weird)
    writePinHigh(B0);
    writePinHigh(B1);
    writePinHigh(B2);
}