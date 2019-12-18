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
typedef  int uint32_t ;

/* Variables and functions */

void coap_option_nibble(uint32_t value, uint8_t *nibble)
{
    if (value<13)
    {
        *nibble = (0xFF & value);
    }
    else
    if (value<=0xFF+13)
    {
        *nibble = 13;
    } else if (value<=0xFFFF+269)
    {
        *nibble = 14;
    }
}