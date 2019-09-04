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
 scalar_t__ PCF8584_DATA ; 
 int /*<<< orphan*/  envctrl_i2c_read_addr (unsigned char) ; 
 int /*<<< orphan*/  envctrl_i2c_read_data () ; 
 int /*<<< orphan*/  envctrl_i2c_stop () ; 
 int /*<<< orphan*/  envctrl_i2c_write_addr (unsigned char) ; 
 int /*<<< orphan*/  envctrl_i2c_write_data (unsigned char) ; 
 scalar_t__ i2c ; 
 unsigned char readb (scalar_t__) ; 

__attribute__((used)) static unsigned char envctrl_i2c_read_8591(unsigned char addr, unsigned char port)
{
	/* Send address. */
	envctrl_i2c_write_addr(addr);

	/* Setup port to read. */
	envctrl_i2c_write_data(port);
	envctrl_i2c_stop();

	/* Read port. */
	envctrl_i2c_read_addr(addr);

	/* Do a single byte read and send stop. */
	envctrl_i2c_read_data();
	envctrl_i2c_stop();

	return readb(i2c + PCF8584_DATA);
}