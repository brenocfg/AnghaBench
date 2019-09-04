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
struct TYPE_3__ {char* op; int o; } ;
typedef  TYPE_1__ ArmOpcode ;

/* Variables and functions */
 int /*<<< orphan*/  strcmpnull (char*,char const*) ; 

__attribute__((used)) static inline int arm_opcode_cond(ArmOpcode *ao, int delta) {
	const char *conds[] = {
		"eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc",
		"hi", "ls", "ge", "lt", "gt", "le", "al", "nv", 0
	};
	int i, cond = 14; // 'always' is default
	char *c = ao->op+delta;
	for (i=0; conds[i]; i++) {
		if (!strcmpnull (c, conds[i])) {
			cond = i;
			break;
		}
	}
	ao->o |= cond << 4;
	return cond;
}