#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct __rebase_struct {TYPE_1__* core; scalar_t__ type; scalar_t__ diff; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  addr; int /*<<< orphan*/  at; } ;
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_2__ RAnalRef ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_xrefs_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __rebase_refs_i(void *user, const ut64 k, const void *v) {
	struct __rebase_struct *reb = (void*)user;
	RAnalRef *ref = (RAnalRef *)v;
	ref->addr += reb->diff;
	ref->at += reb->diff;
	if (reb->type) {
		r_anal_xrefs_set (reb->core->anal, ref->addr, ref->at, ref->type);
	} else {
		r_anal_xrefs_set (reb->core->anal, ref->at, ref->addr, ref->type);
	}
	return true;
}