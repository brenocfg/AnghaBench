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
typedef  int ut8 ;
struct TYPE_5__ {char* mnemonic; int operands_count; TYPE_1__* operands; } ;
struct TYPE_4__ {int type; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_FPUREG ; 
 int OT_REGALL ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int opfcmov(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	char* fcmov = op->mnemonic + strlen("fcmov");
	switch (op->operands_count) {
	case 2:
		if ( op->operands[0].type & OT_FPUREG & ~OT_REGALL && op->operands[0].reg == 0 &&
		     op->operands[1].type & OT_FPUREG & ~OT_REGALL ) {
			if ( !strcmp( fcmov, "b" ) ) {
				data[l++] = 0xda;
				data[l++] = 0xc0 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "e" ) ) {
				data[l++] = 0xda;
				data[l++] = 0xc8 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "be" ) ) {
				data[l++] = 0xda;
				data[l++] = 0xd0 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "u" ) ) {
				data[l++] = 0xda;
				data[l++] = 0xd8 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "nb" ) ) {
				data[l++] = 0xdb;
				data[l++] = 0xc0 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "ne" ) ) {
				data[l++] = 0xdb;
				data[l++] = 0xc8 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "nbe" ) ) {
				data[l++] = 0xdb;
				data[l++] = 0xd0 | op->operands[1].reg;
			} else if ( !strcmp( fcmov, "nu" ) ) {
				data[l++] = 0xdb;
				data[l++] = 0xd8 | op->operands[1].reg;
			} else {
				return -1;
			}
		} else {
			return -1;
		}
		break;
	default:
		return -1;
	}
	return l;
}