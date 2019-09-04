#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f; int /*<<< orphan*/  (* unset_name ) (int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_5__ {TYPE_1__ flb; scalar_t__ (* flg_class_get ) (int /*<<< orphan*/ ,char const*) ;} ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void r_anal_class_unset_flag(RAnal *anal, const char *name) {
	if (!name || !anal->flb.unset_name || !anal->flg_class_get) {
		return;
	}
	if (anal->flg_class_get (anal->flb.f, name)) {
		anal->flb.unset_name (anal->flb.f, name);
	}
}