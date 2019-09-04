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
 int /*<<< orphan*/  envctrl_i2c_read_addr (unsigned char) ; 
 unsigned char envctrl_i2c_read_data () ; 
 int /*<<< orphan*/  envctrl_i2c_stop () ; 

__attribute__((used)) static unsigned char envctrl_i2c_read_8574(unsigned char addr)
{
	unsigned char rd;

	envctrl_i2c_read_addr(addr);

	/* Do a single byte read and send stop. */
	rd = envctrl_i2c_read_data();
	envctrl_i2c_stop();
	return rd;
}