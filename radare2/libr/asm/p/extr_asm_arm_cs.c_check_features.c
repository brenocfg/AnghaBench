#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* detail; } ;
typedef  TYPE_2__ cs_insn ;
struct TYPE_8__ {int /*<<< orphan*/  features; } ;
struct TYPE_6__ {int groups_count; int* groups; } ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
#define  ARM_GRP_ARM 131 
#define  ARM_GRP_THUMB 130 
#define  ARM_GRP_THUMB1ONLY 129 
#define  ARM_GRP_THUMB2 128 
 int /*<<< orphan*/  cd ; 
 char* cs_group_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool check_features(RAsm *a, cs_insn *insn) {
	int i;
	if (!insn || !insn->detail) {
		return true;
	}
	for (i = 0; i < insn->detail->groups_count; i++) {
		int id = insn->detail->groups[i];
		switch (id) {
		case ARM_GRP_ARM:
		case ARM_GRP_THUMB:
		case ARM_GRP_THUMB1ONLY:
		case ARM_GRP_THUMB2:
			continue;
		default:
			if (id < 128) {
				continue;
			}
		}
		const char *name = cs_group_name (cd, id);
		if (!name) {
			return true;
		}
		if (!strstr (a->features, name)) {
			return false;
		}
	}
	return true;
}