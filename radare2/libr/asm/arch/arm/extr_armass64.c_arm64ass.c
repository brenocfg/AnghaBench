#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ArmOp ;

/* Variables and functions */
 int UT32_MAX ; 
 int adr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int adrp (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int arithmetic (TYPE_1__*,int) ; 
 int bdot (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int branch (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int bytelsop (TYPE_1__*,int) ; 
 int cmp (TYPE_1__*) ; 
 int exception (TYPE_1__*,int) ; 
 scalar_t__ handlePAC (int*,char const*) ; 
 int mem_barrier (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mov (TYPE_1__*) ; 
 int msr (TYPE_1__*,int) ; 
 int neg (TYPE_1__*) ; 
 int orr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseOpcode (char const*,TYPE_1__*) ; 
 int reglsop (TYPE_1__*,int) ; 
 int regsluop (TYPE_1__*,int) ; 
 int stp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

bool arm64ass(const char *str, ut64 addr, ut32 *op) {
	ArmOp ops = {0};
	if (!parseOpcode (str, &ops)) {
		return false;
	}
	/* TODO: write tests for this and move out the regsize logic into the mov */
	if (!strncmp (str, "mov", 3)) {
		*op = mov (&ops);
		return *op != -1;
	}
	if (!strncmp (str, "cmp", 3)) {
		*op = cmp (&ops);
		return *op != -1;
	}
	if (!strncmp (str, "ldrb", 4)) {
		*op = bytelsop (&ops, 0x00004039);
		return *op != -1;
	}
	if (!strncmp (str, "ldrh", 4)) {
		*op = bytelsop (&ops, 0x00004078);
		return *op != -1;
	}
	if (!strncmp (str, "ldrsh", 5)) {
		*op = bytelsop (&ops, 0x0000c078);
		return *op != -1;
	}
	if (!strncmp (str, "ldrsw", 5)) {
		*op = bytelsop (&ops, 0x000080b8);
		return *op != -1;
	}
	if (!strncmp (str, "ldrsb", 5)) {
		*op = bytelsop (&ops, 0x0000c039);
		return *op != -1;
	}
	if (!strncmp (str, "strb", 4)) {
		*op = bytelsop (&ops, 0x00000039);
		return *op != -1;
	}
	if (!strncmp (str, "strh", 4)) {
		*op = bytelsop (&ops, 0x00000078);
		return *op != -1;
	}
	if (!strncmp (str, "ldr", 3)) {
		*op = reglsop (&ops, 0x000040f8);
		return *op != -1;
	}
	if (!strncmp (str, "stur", 4)) {
		*op = regsluop (&ops, 0x000000f8);
		return *op != -1;
	}
	if (!strncmp (str, "ldur", 4)) {
		*op = regsluop (&ops, 0x000040f8);
		return *op != -1;
	}
	if (!strncmp (str, "str", 3)) {
		*op = reglsop (&ops, 0x000000f8);
		return *op != -1;
	}
	if (!strncmp (str, "stp", 3)) {
		*op = stp (&ops, 0x000000a9);
		return *op != -1;
	}
	if (!strncmp (str, "ldp", 3)) {
		*op = stp (&ops, 0x000040a9);
		return *op != -1;
	}
	if (!strncmp (str, "sub", 3)) { // w
		*op = arithmetic (&ops, 0xd1);
		return *op != -1;
	}
	if (!strncmp (str, "add x", 5)) {
		*op = arithmetic (&ops, 0x91);
		return *op != -1;
	}
	if (!strncmp (str, "add w", 5)) {
		*op = arithmetic (&ops, 0x11);
		return *op != -1;
	}
	if (!strncmp (str, "adr x", 5)) { // w
		*op = adr (&ops, addr);
		return *op != -1;
	}
	if (!strncmp (str, "adrp x", 6)) {
		*op = adrp (&ops, addr, 0x00000090);
		return *op != -1;
	}
	if (!strncmp (str, "neg", 3)) {
		*op = neg (&ops);
		return *op != -1;
	}
	if (!strcmp (str, "isb")) {
		*op = 0xdf3f03d5;
		return *op != -1;
	}
	// PAC
	if (handlePAC (op, str)) {
		return true;
	}
	if (!strcmp (str, "nop")) {
		*op = 0x1f2003d5;
		return *op != -1;
	}
	if (!strcmp (str, "ret")) {
		*op = 0xc0035fd6;
		return true;
	}
	if (!strncmp (str, "msr ", 4)) {
		*op = msr (&ops, 0);
		if (*op != UT32_MAX) {
			return true;
		}
	}
	if (!strncmp (str, "mrs ", 4)) {
		*op = msr (&ops, 1);
		if (*op != UT32_MAX) {
			return true;
		}
	}
	if (!strncmp (str, "orr ", 4)) {
		*op = orr (&ops, addr);
		return *op != UT32_MAX;
	}
	if (!strncmp (str, "svc ", 4)) { // system level exception
		*op = exception (&ops, 0x010000d4);
		return *op != -1;
	}
	if (!strncmp (str, "hvc ", 4)) { // hypervisor level exception
		*op = exception (&ops, 0x020000d4);
		return *op != -1;
	}
	if (!strncmp (str, "smc ", 4)) { // secure monitor exception
		*op = exception (&ops, 0x030000d4);
		return *op != -1;
	}
	if (!strncmp (str, "brk ", 4)) { // breakpoint
		*op = exception (&ops, 0x000020d4);
		return *op != -1;
	}
	if (!strncmp (str, "hlt ", 4)) { // halt
		*op = exception (&ops, 0x000040d4);
		return *op != -1;
	}
	if (!strncmp (str, "b ", 2)) {
		*op = branch (&ops, addr, 0x14);
		return *op != -1;
	}
	if (!strncmp (str, "b.eq ", 5)) {
		*op = bdot (&ops, addr, 0x00000054);
		return *op != -1;
	}
	if (!strncmp (str, "b.hs ", 5)) {
		*op = bdot (&ops, addr, 0x02000054);
		return *op != -1;
	}
	if (!strncmp (str, "bl ", 3)) {
		*op = branch (&ops, addr, 0x94);
		return *op != -1;
	}
	if (!strncmp (str, "br x", 4)) {
		*op = branch (&ops, addr, 0x1fd6);
		return *op != -1;
	}
	if (!strncmp (str, "blr x", 5)) {
		*op = branch (&ops, addr, 0x3fd6);
		return *op != -1;
	}
	if (!strncmp (str, "dmb ", 4)) {
		*op = mem_barrier (&ops, addr, 0xbf3003d5);
		return *op != -1;
	}
	if (!strncmp (str, "dsb ", 4)) {
		*op = mem_barrier (&ops, addr, 0x9f3003d5);
		return *op != -1;
	}
	if (!strncmp (str, "isb", 3)) {
		*op = mem_barrier (&ops, addr, 0xdf3f03d5);
		return *op != -1;
	}
	return false;
}