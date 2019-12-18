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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  _RAnalCond ;
struct TYPE_3__ {int /*<<< orphan*/  delta; int /*<<< orphan*/  kind; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ RAnalVar ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  ADB ; 
 char* RKEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_array_append_num (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void var_add_range (RAnal *a, RAnalVar *var, _RAnalCond cond, ut64 val) {
	const char *key = RKEY (var->addr, var->kind, var->delta);
	sdb_array_append_num (ADB, key, cond, 0);
	sdb_array_append_num (ADB, key, val, 0);
}