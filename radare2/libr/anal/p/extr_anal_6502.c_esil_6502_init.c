#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {scalar_t__ reg; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_reg_get (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  r_reg_set_value (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esil_6502_init (RAnalEsil *esil) {
	if (esil->anal && esil->anal->reg) {		//initial values
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "pc", -1), 0x0000);
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "sp", -1), 0xff);
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "a", -1), 0x00);
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "x", -1), 0x00);
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "y", -1), 0x00);
		r_reg_set_value (esil->anal->reg, r_reg_get (esil->anal->reg, "flags", -1), 0x00);
	}
	return true;
}