#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nattributes; int* attributes; } ;
typedef  TYPE_1__ MVDependency ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  bms_is_member (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
dependency_is_fully_matched(MVDependency *dependency, Bitmapset *attnums)
{
	int			j;

	/*
	 * Check that the dependency actually is fully covered by clauses. We have
	 * to translate all attribute numbers, as those are referenced
	 */
	for (j = 0; j < dependency->nattributes; j++)
	{
		int			attnum = dependency->attributes[j];

		if (!bms_is_member(attnum, attnums))
			return false;
	}

	return true;
}