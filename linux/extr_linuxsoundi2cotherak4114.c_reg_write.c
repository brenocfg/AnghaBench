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
struct ak4114 {unsigned char* regmap; unsigned char* txcsb; int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,unsigned char,unsigned char) ;} ;

/* Variables and functions */
 unsigned char AK4114_REG_INT1_MASK ; 
 unsigned char AK4114_REG_TXCSB0 ; 
 unsigned char AK4114_REG_TXCSB4 ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void reg_write(struct ak4114 *ak4114, unsigned char reg, unsigned char val)
{
	ak4114->write(ak4114->private_data, reg, val);
	if (reg <= AK4114_REG_INT1_MASK)
		ak4114->regmap[reg] = val;
	else if (reg >= AK4114_REG_TXCSB0 && reg <= AK4114_REG_TXCSB4)
		ak4114->txcsb[reg-AK4114_REG_TXCSB0] = val;
}