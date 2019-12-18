#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * reflines; } ;
struct TYPE_6__ {int /*<<< orphan*/  prev_line_col; int /*<<< orphan*/  refline2; int /*<<< orphan*/  refline; TYPE_1__* core; } ;
struct TYPE_5__ {TYPE_3__* anal; } ;
typedef  TYPE_2__ RDisasmState ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds_reflines_fini(RDisasmState *ds) {
	RAnal *anal = ds->core->anal;
	r_list_free (anal->reflines);
	anal->reflines = NULL;
	R_FREE (ds->refline);
	R_FREE (ds->refline2);
	R_FREE (ds->prev_line_col);
}