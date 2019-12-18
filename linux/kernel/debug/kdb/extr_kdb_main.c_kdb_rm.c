#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
 int KDB_ARGCOUNT ; 
 int KDB_BADREG ; 
 TYPE_1__* dbg_reg_def ; 
 int /*<<< orphan*/  dbg_set_reg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kdb_check_regs () ; 
 int /*<<< orphan*/  kdb_current_regs ; 
 int /*<<< orphan*/  kdb_printf (char*) ; 
 int kdbgetu64arg (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdb_rm(int argc, const char **argv)
{
#if DBG_MAX_REG_NUM > 0
	int diag;
	const char *rname;
	int i;
	u64 reg64;
	u32 reg32;
	u16 reg16;
	u8 reg8;

	if (argc != 2)
		return KDB_ARGCOUNT;
	/*
	 * Allow presence or absence of leading '%' symbol.
	 */
	rname = argv[1];
	if (*rname == '%')
		rname++;

	diag = kdbgetu64arg(argv[2], &reg64);
	if (diag)
		return diag;

	diag = kdb_check_regs();
	if (diag)
		return diag;

	diag = KDB_BADREG;
	for (i = 0; i < DBG_MAX_REG_NUM; i++) {
		if (strcmp(rname, dbg_reg_def[i].name) == 0) {
			diag = 0;
			break;
		}
	}
	if (!diag) {
		switch(dbg_reg_def[i].size * 8) {
		case 8:
			reg8 = reg64;
			dbg_set_reg(i, &reg8, kdb_current_regs);
			break;
		case 16:
			reg16 = reg64;
			dbg_set_reg(i, &reg16, kdb_current_regs);
			break;
		case 32:
			reg32 = reg64;
			dbg_set_reg(i, &reg32, kdb_current_regs);
			break;
		case 64:
			dbg_set_reg(i, &reg64, kdb_current_regs);
			break;
		}
	}
	return diag;
#else
	kdb_printf("ERROR: Register set currently not implemented\n");
    return 0;
#endif
}