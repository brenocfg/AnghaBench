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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int r_core_print_disasm_instructions (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __disasm(void *_core, ut64 addr) {
	RCore *core = _core;
	ut64 prevaddr = core->offset;
	int len;

	r_core_seek (core, addr, true);
	len = r_core_print_disasm_instructions (core, 0, 1);
	r_core_seek (core, prevaddr, true);

	return len;
}