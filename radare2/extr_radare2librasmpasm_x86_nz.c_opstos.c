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
typedef  int ut8 ;
struct TYPE_4__ {int /*<<< orphan*/  mnemonic; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_1__ Opcode ;

/* Variables and functions */
 int /*<<< orphan*/  is_valid_registers (TYPE_1__ const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opstos(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	if (!strcmp(op->mnemonic, "stosw")) {
		data[l++] = 0x66;
	}
	if (!strcmp(op->mnemonic, "stosb")) {
		data[l++] = 0xaa;
	} else if (!strcmp(op->mnemonic, "stosw")) {
		data[l++] = 0xab;
	} else if (!strcmp(op->mnemonic, "stosd")) {
		data[l++] = 0xab;
	}
	return l;
}