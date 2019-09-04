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
 int BCM590XX_CSRVOUT1 ; 
 int BCM590XX_GPLDO1CTRL ; 
 int BCM590XX_REG_CSR ; 
 scalar_t__ BCM590XX_REG_IS_GPLDO (int) ; 
 scalar_t__ BCM590XX_REG_IS_LDO (int) ; 
 int BCM590XX_RFLDOCTRL ; 

__attribute__((used)) static int bcm590xx_get_vsel_register(int id)
{
	if (BCM590XX_REG_IS_LDO(id))
		return BCM590XX_RFLDOCTRL + id;
	else if (BCM590XX_REG_IS_GPLDO(id))
		return BCM590XX_GPLDO1CTRL + id;
	else
		return BCM590XX_CSRVOUT1 + (id - BCM590XX_REG_CSR) * 3;
}