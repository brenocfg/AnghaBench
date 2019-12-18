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

/* Variables and functions */
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  i2c_init () ; 
 int i2c_initialized ; 

uint8_t init_mcp23017(void)
{
    i2c_initialized = false;

    if (i2c_initialized == 0)
    {
        i2c_init();  // on pins D(1,0)
        _delay_ms(1000);
    }

    return 0;
}