#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_13__ {int bits; int /*<<< orphan*/  reg; } ;
struct TYPE_12__ {int /*<<< orphan*/  esil; } ;
struct TYPE_11__ {TYPE_4__* anal; } ;
struct TYPE_10__ {int size; } ;
typedef  TYPE_1__ RRegItem ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ RAnal ;

/* Variables and functions */
 int R_ANAL_OP_MASK_ESIL ; 
 int R_ANAL_OP_MASK_VAL ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_anal_op_free (TYPE_3__*) ; 
 TYPE_3__* r_core_anal_op (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 char* r_reg_32_to_64 (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* r_reg_get (int /*<<< orphan*/ ,char*,int) ; 
 char const* r_strbuf_get (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void get_src_regname(RCore *core, ut64 addr, char *regname, int size) {
	RAnal *anal = core->anal;
	RAnalOp *op = r_core_anal_op (core, addr, R_ANAL_OP_MASK_VAL | R_ANAL_OP_MASK_ESIL);
	if (!op) {
		return;
	}
	char *op_esil = strdup (r_strbuf_get (&op->esil));
	char *tmp = strchr (op_esil, ',');
	if (tmp) {
		*tmp = '\0';
	}
	memset (regname, 0, size);
	RRegItem *ri = r_reg_get (anal->reg, op_esil, -1);
	if (ri) {
		if ((anal->bits == 64) && (ri->size == 32)) {
			const char *reg = r_reg_32_to_64 (anal->reg, op_esil);
			if (reg) {
				free (op_esil);
				op_esil = strdup (reg);
			}
		}
		strncpy (regname, op_esil, size - 1);
	}
	free (op_esil);
	r_anal_op_free (op);
}