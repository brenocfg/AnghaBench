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
 int /*<<< orphan*/  D0 ; 
 int /*<<< orphan*/  D1 ; 
 int /*<<< orphan*/  D4 ; 
 int /*<<< orphan*/  D6 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void backlight_init_ports(void) {
	setPinOutput(D0);
	setPinOutput(D1);
	setPinOutput(D4);
	setPinOutput(D6);

	writePinLow(D0);
	writePinLow(D1);
	writePinLow(D4);
	writePinLow(D6);
}