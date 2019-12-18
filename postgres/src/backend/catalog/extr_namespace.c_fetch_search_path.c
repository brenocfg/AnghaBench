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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessTempTableNamespace (int) ; 
 scalar_t__ activeCreationNamespace ; 
 int /*<<< orphan*/  activeSearchPath ; 
 scalar_t__ activeTempCreationPending ; 
 scalar_t__ linitial_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recomputeNamespacePath () ; 

List *
fetch_search_path(bool includeImplicit)
{
	List	   *result;

	recomputeNamespacePath();

	/*
	 * If the temp namespace should be first, force it to exist.  This is so
	 * that callers can trust the result to reflect the actual default
	 * creation namespace.  It's a bit bogus to do this here, since
	 * current_schema() is supposedly a stable function without side-effects,
	 * but the alternatives seem worse.
	 */
	if (activeTempCreationPending)
	{
		AccessTempTableNamespace(true);
		recomputeNamespacePath();
	}

	result = list_copy(activeSearchPath);
	if (!includeImplicit)
	{
		while (result && linitial_oid(result) != activeCreationNamespace)
			result = list_delete_first(result);
	}

	return result;
}