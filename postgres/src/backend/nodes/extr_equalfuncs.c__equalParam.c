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
typedef  int /*<<< orphan*/  Param ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  paramcollid ; 
 int /*<<< orphan*/  paramid ; 
 int /*<<< orphan*/  paramkind ; 
 int /*<<< orphan*/  paramtype ; 
 int /*<<< orphan*/  paramtypmod ; 

__attribute__((used)) static bool
_equalParam(const Param *a, const Param *b)
{
	COMPARE_SCALAR_FIELD(paramkind);
	COMPARE_SCALAR_FIELD(paramid);
	COMPARE_SCALAR_FIELD(paramtype);
	COMPARE_SCALAR_FIELD(paramtypmod);
	COMPARE_SCALAR_FIELD(paramcollid);
	COMPARE_LOCATION_FIELD(location);

	return true;
}