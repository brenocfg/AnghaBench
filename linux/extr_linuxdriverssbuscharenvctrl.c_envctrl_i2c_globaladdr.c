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
struct i2c_child_t {int dummy; } ;

/* Variables and functions */
 unsigned char ENVCTRL_GLOBALADDR_ADDR_MASK ; 

__attribute__((used)) static int envctrl_i2c_globaladdr(struct i2c_child_t *pchild,
				  unsigned char data,
				  char *bufdata)
{
	/* Translatation table is not necessary, as global
	 * addr is the integer value of the GA# bits.
	 *
	 * NOTE: MSB is documented as zero, but I see it as '1' always....
	 *
	 * -----------------------------------------------
	 * | 0 | FAL | DEG | GA4 | GA3 | GA2 | GA1 | GA0 |
	 * -----------------------------------------------
	 * GA0 - GA4	integer value of Global Address (backplane slot#)
	 * DEG			0 = cPCI Power supply output is starting to degrade
	 * 				1 = cPCI Power supply output is OK
	 * FAL			0 = cPCI Power supply has failed
	 * 				1 = cPCI Power supply output is OK
	 */
	bufdata[0] = (data & ENVCTRL_GLOBALADDR_ADDR_MASK);
	return 1;
}