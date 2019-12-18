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
struct TYPE_3__ {scalar_t__* attributes; int nattributes; } ;
typedef  TYPE_1__ MVDependency ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */

__attribute__((used)) static bool
dependency_implies_attribute(MVDependency *dependency, AttrNumber attnum)
{
	if (attnum == dependency->attributes[dependency->nattributes - 1])
		return true;

	return false;
}