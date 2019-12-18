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
typedef  char TYPCATEGORY ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char TYPCATEGORY_INVALID ; 
 int /*<<< orphan*/  get_type_category_preferred (int /*<<< orphan*/ ,char*,int*) ; 

bool
IsPreferredType(TYPCATEGORY category, Oid type)
{
	char		typcategory;
	bool		typispreferred;

	get_type_category_preferred(type, &typcategory, &typispreferred);
	if (category == typcategory || category == TYPCATEGORY_INVALID)
		return typispreferred;
	else
		return false;
}