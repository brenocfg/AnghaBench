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
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 int r_sign_add_bb_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool addFcnHash(RCore *core, RAnalFunction *fcn, const char *name) {
	r_return_val_if_fail (core && fcn && name, false);
	return r_sign_add_bb_hash (core->anal, fcn, name);
}