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
struct TYPE_3__ {int /*<<< orphan*/ * j; int /*<<< orphan*/ * anal; } ;
typedef  int /*<<< orphan*/  RAnal ;
typedef  int /*<<< orphan*/  PJ ;
typedef  TYPE_1__ ListJsonCtx ;

/* Variables and functions */
 int /*<<< orphan*/  pj_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_class_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_anal_class_list_json_cb ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_anal_class_list_json(RAnal *anal) {
	PJ *j = pj_new ();
	if (!j) {
		return;
	}
	pj_a (j);

	ListJsonCtx ctx;
	ctx.anal = anal;
	ctx.j = j;
	r_anal_class_foreach (anal, r_anal_class_list_json_cb, &ctx);

	pj_end (j);
	r_cons_printf ("%s\n", pj_string (j));
	pj_free (j);
}