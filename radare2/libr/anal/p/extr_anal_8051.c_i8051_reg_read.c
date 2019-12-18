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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  RRegItem ;
typedef  int /*<<< orphan*/  RReg ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 int /*<<< orphan*/ * r_reg_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut32 i8051_reg_read (RReg *reg, const char *regname) {
	if (reg) {
		RRegItem *item = r_reg_get (reg, regname, R_REG_TYPE_GPR);
		if (item) {
			return r_reg_get_value (reg, item);
		}
	}
	return 0;
}