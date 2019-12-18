#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dpns ;
struct TYPE_4__ {int /*<<< orphan*/ * rtable_names; int /*<<< orphan*/  ctes; int /*<<< orphan*/ * rtable; } ;
typedef  TYPE_1__ deparse_namespace ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_rtable_names (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

List *
select_rtable_names_for_explain(List *rtable, Bitmapset *rels_used)
{
	deparse_namespace dpns;

	memset(&dpns, 0, sizeof(dpns));
	dpns.rtable = rtable;
	dpns.ctes = NIL;
	set_rtable_names(&dpns, NIL, rels_used);
	/* We needn't bother computing column aliases yet */

	return dpns.rtable_names;
}