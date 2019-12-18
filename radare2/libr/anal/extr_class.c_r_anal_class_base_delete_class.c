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
struct TYPE_3__ {char const* member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  RAnal ;
typedef  TYPE_1__ DeleteClassCtx ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_class_base_delete_class_cb ; 
 int /*<<< orphan*/  r_anal_class_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void r_anal_class_base_delete_class(RAnal *anal, const char *class_name) {
	DeleteClassCtx ctx = { anal, class_name };
	r_anal_class_foreach (anal, r_anal_class_base_delete_class_cb, &ctx);
}