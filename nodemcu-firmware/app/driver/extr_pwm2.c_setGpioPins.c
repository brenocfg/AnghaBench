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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUT_W1TC_ADDRESS ; 
 int /*<<< orphan*/  GPIO_OUT_W1TS_ADDRESS ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static inline void setGpioPins(const uint16_t enabledGpioMask, const register uint16_t maskOn) {
  GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, maskOn);
  const register uint16_t maskOff = ~maskOn & enabledGpioMask;
  GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, maskOff);
}