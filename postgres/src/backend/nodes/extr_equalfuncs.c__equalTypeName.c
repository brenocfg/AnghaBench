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
typedef  int /*<<< orphan*/  TypeName ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arrayBounds ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  pct_type ; 
 int /*<<< orphan*/  setof ; 
 int /*<<< orphan*/  typeOid ; 
 int /*<<< orphan*/  typemod ; 
 int /*<<< orphan*/  typmods ; 

__attribute__((used)) static bool
_equalTypeName(const TypeName *a, const TypeName *b)
{
	COMPARE_NODE_FIELD(names);
	COMPARE_SCALAR_FIELD(typeOid);
	COMPARE_SCALAR_FIELD(setof);
	COMPARE_SCALAR_FIELD(pct_type);
	COMPARE_NODE_FIELD(typmods);
	COMPARE_SCALAR_FIELD(typemod);
	COMPARE_NODE_FIELD(arrayBounds);
	COMPARE_LOCATION_FIELD(location);

	return true;
}