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
#define  TAS_REG_ACS 130 
#define  TAS_REG_MCS 129 
#define  TAS_REG_MCS2 128 
 int send_init_client (struct pmac_keywest*,unsigned int*) ; 

__attribute__((used)) static int snapper_init_client(struct pmac_keywest *i2c)
{
	static unsigned int regs[] = {
		/* normal operation, SCLK=64fps, i2s output, 16bit width */
		TAS_REG_MCS, (1<<6)|(2<<4)|0,
		/* normal operation, all-pass mode */
		TAS_REG_MCS2, (1<<1),
		/* normal output, no deemphasis, A input, power-up, line-in */
		TAS_REG_ACS, 0,
		0, /* terminator */
	};
	DBG("(I) snapper init client\n");
	return send_init_client(i2c, regs);
}