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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUT_W1TC_ADDRESS ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws2801_bit_data ; 
 int /*<<< orphan*/  ws2801_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ws2801_strip(uint8_t const * data, uint16_t len) {
    while (len--) {
        ws2801_byte(*(data++));
    }
    GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, ws2801_bit_data);
}