#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPropertyList (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
show_eval_params(Bitmapset *bms_params, ExplainState *es)
{
	int			paramid = -1;
	List	   *params = NIL;

	Assert(bms_params);

	while ((paramid = bms_next_member(bms_params, paramid)) >= 0)
	{
		char		param[32];

		snprintf(param, sizeof(param), "$%d", paramid);
		params = lappend(params, pstrdup(param));
	}

	if (params)
		ExplainPropertyList("Params Evaluated", params, es);
}