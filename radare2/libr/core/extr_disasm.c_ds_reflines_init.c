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
struct TYPE_9__ {int /*<<< orphan*/ * reflines; } ;
struct TYPE_8__ {int /*<<< orphan*/  show_lines_call; int /*<<< orphan*/  linesout; int /*<<< orphan*/  l; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; scalar_t__ pj; scalar_t__ show_lines_bb; TYPE_1__* core; } ;
struct TYPE_7__ {TYPE_3__* anal; } ;
typedef  TYPE_2__ RDisasmState ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  ds_reflines_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  lastaddr ; 
 int /*<<< orphan*/ * r_anal_reflines_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds_reflines_init(RDisasmState *ds) {
	RAnal *anal = ds->core->anal;

	lastaddr = UT64_MAX;

	if (ds->show_lines_bb || ds->pj) {
		ds_reflines_fini (ds);
		anal->reflines = r_anal_reflines_get (anal,
			ds->addr, ds->buf, ds->len, ds->l,
			ds->linesout, ds->show_lines_call);
	} else {
		r_list_free (anal->reflines);
		anal->reflines = NULL;
	}
}