#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  mnemonic; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RCore ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int R_ANAL_OP_MASK_BASIC ; 
 int R_ANAL_OP_MASK_DISASM ; 
 int R_ANAL_OP_MASK_HINT ; 
 char* r_anal_op_family_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_op_free (TYPE_1__*) ; 
 char* r_anal_optype_to_string (int /*<<< orphan*/ ) ; 
 TYPE_1__* r_core_anal_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdb_num_inc (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void __updateStats(RCore *core, Sdb *db, ut64 addr, int statsMode) {
	RAnalOp *op = r_core_anal_op (core, addr, R_ANAL_OP_MASK_BASIC | R_ANAL_OP_MASK_HINT | R_ANAL_OP_MASK_DISASM);
	if (!op) {
		return;
	}
	if (statsMode == 'f') {
		const char *family = r_anal_op_family_to_string (op->family);
		sdb_num_inc (db, family, 1, 0);
	} else if (statsMode == 'o') {
		const char *type = r_anal_optype_to_string (op->type);
		sdb_num_inc (db, type, 1, 0);
	} else {
		char *mnem = strdup (op->mnemonic);
		char *sp = strstr (mnem, " ");
		if (sp) {
			*sp = 0;
			//memmove (mnem, sp + 1, strlen (sp));
		}
		sdb_num_inc (db, mnem, 1, 0);
	}
	//sdb_set (db, family, "1", 0);
	//r_cons_printf ("0x%08"PFMT64x" %s\n", addr, family);
	r_anal_op_free (op);
	// r_core_cmdf (core, "pd 1 @ 0x%08"PFMT64x"\n", addr);
}