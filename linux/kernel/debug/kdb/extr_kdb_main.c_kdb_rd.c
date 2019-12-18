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
 char* dbg_get_reg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dbg_reg_def ; 
 int kdb_check_regs () ; 
 int /*<<< orphan*/  kdb_current_regs ; 
 int /*<<< orphan*/  kdb_dumpregs (int /*<<< orphan*/ ) ; 
 scalar_t__ kdb_printf (char*,...) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdb_rd(int argc, const char **argv)
{
	int len = kdb_check_regs();
#if DBG_MAX_REG_NUM > 0
	int i;
	char *rname;
	int rsize;
	u64 reg64;
	u32 reg32;
	u16 reg16;
	u8 reg8;

	if (len)
		return len;

	for (i = 0; i < DBG_MAX_REG_NUM; i++) {
		rsize = dbg_reg_def[i].size * 2;
		if (rsize > 16)
			rsize = 2;
		if (len + strlen(dbg_reg_def[i].name) + 4 + rsize > 80) {
			len = 0;
			kdb_printf("\n");
		}
		if (len)
			len += kdb_printf("  ");
		switch(dbg_reg_def[i].size * 8) {
		case 8:
			rname = dbg_get_reg(i, &reg8, kdb_current_regs);
			if (!rname)
				break;
			len += kdb_printf("%s: %02x", rname, reg8);
			break;
		case 16:
			rname = dbg_get_reg(i, &reg16, kdb_current_regs);
			if (!rname)
				break;
			len += kdb_printf("%s: %04x", rname, reg16);
			break;
		case 32:
			rname = dbg_get_reg(i, &reg32, kdb_current_regs);
			if (!rname)
				break;
			len += kdb_printf("%s: %08x", rname, reg32);
			break;
		case 64:
			rname = dbg_get_reg(i, &reg64, kdb_current_regs);
			if (!rname)
				break;
			len += kdb_printf("%s: %016llx", rname, reg64);
			break;
		default:
			len += kdb_printf("%s: ??", dbg_reg_def[i].name);
		}
	}
	kdb_printf("\n");
#else
	if (len)
		return len;

	kdb_dumpregs(kdb_current_regs);
#endif
	return 0;
}