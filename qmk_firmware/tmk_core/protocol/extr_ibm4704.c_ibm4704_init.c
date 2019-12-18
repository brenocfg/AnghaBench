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
 int /*<<< orphan*/  IBM4704_INT_INIT () ; 
 int /*<<< orphan*/  IBM4704_INT_ON () ; 
 int /*<<< orphan*/  idle () ; 
 int /*<<< orphan*/  inhibit () ; 

void ibm4704_init(void) {
    inhibit();  // keep keyboard from sending
    IBM4704_INT_INIT();
    IBM4704_INT_ON();
    idle();  // allow keyboard sending
}