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
 unsigned char OBD_SEND_START ; 
 unsigned char OBD_SEND_STOP ; 
 scalar_t__ PCF8584_CSR ; 
 scalar_t__ PCF8584_DATA ; 
 int STATUS_LRB ; 
 int /*<<< orphan*/  envctrl_i2c_test_bb () ; 
 int /*<<< orphan*/  envtrl_i2c_test_pin () ; 
 scalar_t__ i2c ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int envctrl_i2c_read_addr(unsigned char addr)
{
	envctrl_i2c_test_bb();

	/* Load address. */
	writeb(addr + 1, i2c + PCF8584_DATA);

	envctrl_i2c_test_bb();

	writeb(OBD_SEND_START, i2c + PCF8584_CSR);

	/* Wait for PIN. */
	envtrl_i2c_test_pin();

	/* CSR 0 means acknowledged. */
	if (!(readb(i2c + PCF8584_CSR) & STATUS_LRB)) {
		return readb(i2c + PCF8584_DATA);
	} else {
		writeb(OBD_SEND_STOP, i2c + PCF8584_CSR);
		return 0;
	}
}