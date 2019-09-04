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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUTPUT_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOP ; 
 int /*<<< orphan*/  PLATFORM_GPIO_HIGH ; 
 int /*<<< orphan*/  PLATFORM_GPIO_LOW ; 

__attribute__((used)) static inline void apa102_send_byte(uint32_t data_pin, uint32_t clock_pin, uint8_t byte) {
  int i;
  for (i = 0; i < 8; i++) {
    if (byte & 0x80) {
      GPIO_OUTPUT_SET(data_pin, PLATFORM_GPIO_HIGH); // Set pin high
    } else {
      GPIO_OUTPUT_SET(data_pin, PLATFORM_GPIO_LOW); // Set pin low
    }
    GPIO_OUTPUT_SET(clock_pin, PLATFORM_GPIO_HIGH); // Set pin high
    byte <<= 1;
    NOP;
    NOP;
    GPIO_OUTPUT_SET(clock_pin, PLATFORM_GPIO_LOW); // Set pin low
    NOP;
    NOP;
  }
}