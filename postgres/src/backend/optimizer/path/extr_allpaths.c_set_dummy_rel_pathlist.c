#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lateral_relids; void* partial_pathlist; void* pathlist; TYPE_1__* reltarget; scalar_t__ rows; } ;
struct TYPE_7__ {scalar_t__ width; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 void* NIL ; 
 int /*<<< orphan*/  add_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ create_append_path (int /*<<< orphan*/ *,TYPE_2__*,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  set_cheapest (TYPE_2__*) ; 

__attribute__((used)) static void
set_dummy_rel_pathlist(RelOptInfo *rel)
{
	/* Set dummy size estimates --- we leave attr_widths[] as zeroes */
	rel->rows = 0;
	rel->reltarget->width = 0;

	/* Discard any pre-existing paths; no further need for them */
	rel->pathlist = NIL;
	rel->partial_pathlist = NIL;

	/* Set up the dummy path */
	add_path(rel, (Path *) create_append_path(NULL, rel, NIL, NIL,
											  NIL, rel->lateral_relids,
											  0, false, NIL, -1));

	/*
	 * We set the cheapest-path fields immediately, just in case they were
	 * pointing at some discarded path.  This is redundant when we're called
	 * from set_rel_size(), but not when called from elsewhere, and doing it
	 * twice is harmless anyway.
	 */
	set_cheapest(rel);
}