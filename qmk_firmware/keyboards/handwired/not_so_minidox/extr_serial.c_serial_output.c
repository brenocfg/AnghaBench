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
 int /*<<< orphan*/  SERIAL_PIN_DDR ; 
 int /*<<< orphan*/  SERIAL_PIN_MASK ; 

__attribute__((used)) inline static
void serial_output(void) {
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}