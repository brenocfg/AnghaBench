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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_STATUS_ADDRESS ; 
 int /*<<< orphan*/  GPIO_STATUS_W1TC_ADDRESS ; 
 int /*<<< orphan*/  pin_intr_handler (int /*<<< orphan*/ ) ; 

void pin_intr_handler_iram(void *arg) {
    uint32_t status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, status);
    pin_intr_handler(status);
}