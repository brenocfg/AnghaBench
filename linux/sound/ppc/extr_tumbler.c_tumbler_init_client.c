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
struct pmac_keywest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
#define  TAS_REG_MCS 128 
 int send_init_client (struct pmac_keywest*,unsigned int*) ; 

__attribute__((used)) static int tumbler_init_client(struct pmac_keywest *i2c)
{
	static unsigned int regs[] = {
		/* normal operation, SCLK=64fps, i2s output, i2s input, 16bit width */
		TAS_REG_MCS, (1<<6)|(2<<4)|(2<<2)|0,
		0, /* terminator */
	};
	DBG("(I) tumbler init client\n");
	return send_init_client(i2c, regs);
}