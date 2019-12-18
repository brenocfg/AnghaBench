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
struct ak4117 {unsigned char* regmap; int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,unsigned char,unsigned char) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void reg_write(struct ak4117 *ak4117, unsigned char reg, unsigned char val)
{
	ak4117->write(ak4117->private_data, reg, val);
	if (reg < sizeof(ak4117->regmap))
		ak4117->regmap[reg] = val;
}