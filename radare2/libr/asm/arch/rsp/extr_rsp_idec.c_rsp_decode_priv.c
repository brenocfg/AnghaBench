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
typedef  int ut32 ;
struct TYPE_3__ {int offset; int shift; int mask; } ;
typedef  TYPE_1__ rsp_op_escape ;
typedef  int /*<<< orphan*/  rsp_instruction_priv ;

/* Variables and functions */
 TYPE_1__* rsp_escapes_table ; 
 int /*<<< orphan*/  const* rsp_op_table ; 

__attribute__((used)) static const rsp_instruction_priv* rsp_decode_priv(ut32 iw) {
	const rsp_op_escape* escape;

	/* handle NOP pseudo instruction */
	if (iw == 0) {
		return &rsp_op_table[352];
	}

	escape = &rsp_escapes_table[(iw >> 25)];
	return &rsp_op_table[escape->offset + ((iw >> escape->shift) & escape->mask)];
}