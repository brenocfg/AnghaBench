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
 int /*<<< orphan*/  DefineViewRules (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * UpdateRangeTableOfViewParse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
StoreViewQuery(Oid viewOid, Query *viewParse, bool replace)
{
	/*
	 * The range table of 'viewParse' does not contain entries for the "OLD"
	 * and "NEW" relations. So... add them!
	 */
	viewParse = UpdateRangeTableOfViewParse(viewOid, viewParse);

	/*
	 * Now create the rules associated with the view.
	 */
	DefineViewRules(viewOid, viewParse, replace);
}