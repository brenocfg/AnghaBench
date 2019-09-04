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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ cs_insn ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int cs_disasm (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 

__attribute__((used)) static ut64 lookahead(csh handle, const ut64 addr, const ut8 *buf, int len, int distance) {
	cs_insn *insn = NULL;
	int n = cs_disasm (handle, buf, len, addr, distance, &insn);
	if (n < 1) {
		return UT64_MAX;
	}
	ut64 result = insn[n - 1].address;
	cs_free (insn, n);
	return result;
}