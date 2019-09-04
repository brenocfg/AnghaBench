#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* anal; TYPE_1__* assembler; int /*<<< orphan*/  config; } ;
struct TYPE_9__ {int size; } ;
struct TYPE_8__ {int bits; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int bits; } ;
typedef  TYPE_3__ RRegItem ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_NAME_PC ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* r_reg_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int grab_bits(RCore *core, const char *arg, int *pcbits2) {
	int pcbits = atoi (arg);
	if (pcbits2) {
		*pcbits2 = 0;
	}
	if (pcbits < 1) {
		if (!strcmp (r_config_get (core->config, "asm.arch"), "avr")) {
			pcbits = 8;
			if (pcbits2) {
				*pcbits2 = 32;
			}
		} else {
			const char *pcname = r_reg_get_name (core->anal->reg, R_REG_NAME_PC);
			RRegItem *reg = r_reg_get (core->anal->reg, pcname, 0);
			if (reg) {
				if (core->assembler->bits != reg->size)
					pcbits = reg->size;
			}
		}
	}
	return pcbits ? pcbits : core->anal->bits;
}