#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_7__ {scalar_t__ syntax; } ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 scalar_t__ R_ASM_SYNTAX_ATT ; 
 scalar_t__ VPCEXT2 (int const*,int) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_1__*,char const*) ; 
 char* sdb_fmt (char*,int const,int const) ; 

void decompile_vm(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	const char *buf_asm = "invalid";
	if (len > 3 && buf[0] == 0x0F && buf[1] == 0x3F && (VPCEXT2 (buf, 0x01) || VPCEXT2 (buf, 0x05) || VPCEXT2 (buf, 0x07) || VPCEXT2 (buf, 0x0D) || VPCEXT2 (buf, 0x10))) {
		if (a->syntax == R_ASM_SYNTAX_ATT) {
			buf_asm = sdb_fmt ("vpcext $0x%x, $0x%x", buf[3], buf[2]);
		} else {
			buf_asm = sdb_fmt ("vpcext %xh, %xh", buf[2], buf[3]);
		}
		op->size = 4;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x00 && buf[4] == 0x00) {
		/* 0F C6 28 00 00 vmgetinfo */
		buf_asm ="vmgetinfo";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x00 && buf[4] == 0x01) {
		/* 0F C6 28 00 01 vmsetinfo */
		buf_asm ="vmsetinfo";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x00 && buf[4] == 0x02) {
		/* 0F C6 28 00 02 vmdxdsbl */
		buf_asm ="vmdxdsbl";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x00 && buf[4] == 0x03) {
		/* 0F C6 28 00 03 vmdxenbl */
		buf_asm ="vmdxenbl";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x01 && buf[4] == 0x00) {
		/* 0F C6 28 01 00 vmcpuid */
		buf_asm ="vmcpuid";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x01 && buf[4] == 0x01) {
		/* 0F C6 28 01 01 vmhlt */
		buf_asm ="vmhlt";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x01 && buf[4] == 0x02) {
		/* 0F C6 28 01 02 vmsplaf */
		buf_asm ="vmsplaf";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x02 && buf[4] == 0x00) {
		/* 0F C6 28 02 00 vmpushfd */
		buf_asm ="vmpushfd";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x02 && buf[4] == 0x01) {
		/* 0F C6 28 02 01 vmpopfd */
		buf_asm ="vmpopfd";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x02 && buf[4] == 0x02) {
		/* 0F C6 28 02 02 vmcli */
		buf_asm ="vmcli";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x02 && buf[4] == 0x03) {
		/* 0F C6 28 02 03 vmsti */
		buf_asm ="vmsti";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x02 && buf[4] == 0x04) {
		/* 0F C6 28 02 04 vmiretd */
		buf_asm ="vmiretd";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x03 && buf[4] == 0x00) {
		/* 0F C6 28 03 00 vmsgdt */
		buf_asm ="vmsgdt";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x03 && buf[4] == 0x01) {
		/* 0F C6 28 03 01 vmsidt */
		buf_asm ="vmsidt";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x03 && buf[4] == 0x02) {
		/* 0F C6 28 03 02 vmsldt */
		buf_asm ="vmsldt";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x03 && buf[4] == 0x03) {
		/* 0F C6 28 03 03 vmstr */
		buf_asm ="vmstr";
		op->size = 5;
	} else if (len > 4 && buf[0] == 0x0F && buf[1] == 0xC6 && buf[2] == 0x28 && buf[3] == 0x04 && buf[4] == 0x00) {
		/* 0F C6 28 04 00 vmsdte */
		buf_asm ="vmsdte";
		op->size = 5;
	}
	r_asm_op_set_asm (op, buf_asm);
}