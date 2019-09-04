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
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  write_address (unsigned char) ; 

__attribute__((used)) static void isapnp_key(void)
{
	unsigned char code = 0x6a, msb;
	int i;

	mdelay(1);
	write_address(0x00);
	write_address(0x00);

	write_address(code);

	for (i = 1; i < 32; i++) {
		msb = ((code & 0x01) ^ ((code & 0x02) >> 1)) << 7;
		code = (code >> 1) | msb;
		write_address(code);
	}
}