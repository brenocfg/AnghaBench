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
typedef  int /*<<< orphan*/  SetToDefault ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collation ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  typeId ; 
 int /*<<< orphan*/  typeMod ; 

__attribute__((used)) static bool
_equalSetToDefault(const SetToDefault *a, const SetToDefault *b)
{
	COMPARE_SCALAR_FIELD(typeId);
	COMPARE_SCALAR_FIELD(typeMod);
	COMPARE_SCALAR_FIELD(collation);
	COMPARE_LOCATION_FIELD(location);

	return true;
}