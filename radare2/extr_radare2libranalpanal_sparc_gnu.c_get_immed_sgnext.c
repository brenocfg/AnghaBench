#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ut8 ;
typedef  int const ut64 ;
typedef  int /*<<< orphan*/  st64 ;

/* Variables and functions */

__attribute__((used)) static st64 get_immed_sgnext(const ut64 insn, const ut8 nbit) {
	const ut64 mask = ~(((ut64)1 << (nbit + 1)) - 1);
	return (st64) ((insn & ~mask)
		| (((insn & ((ut64)1 << nbit)) >> nbit) * mask));
}