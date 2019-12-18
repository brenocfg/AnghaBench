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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

void nn_puts (uint8_t *buf, uint16_t val)
{
    buf [0] = (uint8_t) (((val) >> 8) & 0xff);
    buf [1] = (uint8_t) (val & 0xff);
}