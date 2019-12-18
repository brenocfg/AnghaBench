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
typedef  int /*<<< orphan*/  TYPCATEGORY ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char TYPCATEGORY_INVALID ; 
 int /*<<< orphan*/  get_type_category_preferred (int /*<<< orphan*/ ,char*,int*) ; 

TYPCATEGORY
TypeCategory(Oid type)
{
	char		typcategory;
	bool		typispreferred;

	get_type_category_preferred(type, &typcategory, &typispreferred);
	Assert(typcategory != TYPCATEGORY_INVALID);
	return (TYPCATEGORY) typcategory;
}