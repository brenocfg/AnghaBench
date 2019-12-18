#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_printf (char*) ; 
 TYPE_1__* PIN_IRQ ; 
 int /*<<< orphan*/  extint_disable (int /*<<< orphan*/ ) ; 

void SpiPauseSpi(void) {
    DEBUG_printf("SpiPauseSpi\n");
    extint_disable(PIN_IRQ->pin);
}