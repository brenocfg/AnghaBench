#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {int /*<<< orphan*/  f; int /*<<< orphan*/  (* unset ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_9__ {TYPE_1__ flb; int /*<<< orphan*/  (* flg_class_set ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__* (* flg_class_get ) (int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ RFlagItem ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 TYPE_2__* stub1 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_anal_class_rename_flag(RAnal *anal, const char *old_name, const char *new_name) {
	if (!old_name || !new_name || !anal->flb.unset || !anal->flg_class_get || !anal->flg_class_set) {
		return;
	}
	RFlagItem *flag = anal->flg_class_get (anal->flb.f, old_name);
	if (!flag) {
		return;
	}
	ut64 addr = flag->offset;
	anal->flb.unset (anal->flb.f, flag);
	anal->flg_class_set (anal->flb.f, new_name, addr, 0);
}