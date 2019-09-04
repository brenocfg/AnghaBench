#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {int bits; } ;
typedef  TYPE_1__ RAsm ;
typedef  int /*<<< orphan*/  Opcode ;

/* Variables and functions */
 int /*<<< orphan*/  is_valid_registers (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int opcdqe(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	if (a->bits == 64) {
		data[l++] = 0x48;
	}
	data[l++] = 0x98;
	return l;
}