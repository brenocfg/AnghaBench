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
struct TYPE_4__ {scalar_t__ verbose; int /*<<< orphan*/  rtable; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_qual (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static void
show_upper_qual(List *qual, const char *qlabel,
				PlanState *planstate, List *ancestors,
				ExplainState *es)
{
	bool		useprefix;

	useprefix = (list_length(es->rtable) > 1 || es->verbose);
	show_qual(qual, qlabel, planstate, ancestors, useprefix, es);
}