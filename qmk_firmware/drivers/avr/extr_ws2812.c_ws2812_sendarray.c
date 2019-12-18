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
 int RGB_DI_PIN ; 
 int /*<<< orphan*/  _BV (int) ; 
 int /*<<< orphan*/  ws2812_sendarray_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ws2812_sendarray(uint8_t *data, uint16_t datlen) { ws2812_sendarray_mask(data, datlen, _BV(RGB_DI_PIN & 0xF)); }