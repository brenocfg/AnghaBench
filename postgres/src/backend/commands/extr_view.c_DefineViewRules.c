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
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SELECT ; 
 int /*<<< orphan*/  DefineQueryRewrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ViewSelectRuleName ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DefineViewRules(Oid viewOid, Query *viewParse, bool replace)
{
	/*
	 * Set up the ON SELECT rule.  Since the query has already been through
	 * parse analysis, we use DefineQueryRewrite() directly.
	 */
	DefineQueryRewrite(pstrdup(ViewSelectRuleName),
					   viewOid,
					   NULL,
					   CMD_SELECT,
					   true,
					   replace,
					   list_make1(viewParse));

	/*
	 * Someday: automatic ON INSERT, etc
	 */
}