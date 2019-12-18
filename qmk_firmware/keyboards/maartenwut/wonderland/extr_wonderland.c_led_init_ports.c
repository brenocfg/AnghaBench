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
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  B2 ; 
 int /*<<< orphan*/  B3 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 

void led_init_ports(void) {
    // * Set our LED pins as output
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
}