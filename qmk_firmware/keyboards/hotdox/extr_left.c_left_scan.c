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

/* Variables and functions */
 int /*<<< orphan*/  HOTDOX_I2C_TIMEOUT ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int i2c_initialized ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  left_config () ; 
 int /*<<< orphan*/  print (char*) ; 

void left_scan(void)
{
    uint8_t ret = i2c_start(I2C_ADDR_WRITE, HOTDOX_I2C_TIMEOUT);

    if (ret == 0)
    {
        i2c_stop();

        if (!i2c_initialized)
        {
            i2c_initialized = true;
            left_config();
            clear_keyboard();
            print("mcp23017 attached!!!\n");
        }
    }
    else
    {
        if (i2c_initialized)
        {
            i2c_initialized = false;
            clear_keyboard();
            print("mcp23017 deattached!!!\n");
        }
    }

    return;
}