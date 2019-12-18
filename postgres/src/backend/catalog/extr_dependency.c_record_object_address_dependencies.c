#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  numrefs; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  DependencyType ;

/* Variables and functions */
 int /*<<< orphan*/  eliminate_duplicate_dependencies (TYPE_1__*) ; 
 int /*<<< orphan*/  recordMultipleDependencies (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
record_object_address_dependencies(const ObjectAddress *depender,
								   ObjectAddresses *referenced,
								   DependencyType behavior)
{
	eliminate_duplicate_dependencies(referenced);
	recordMultipleDependencies(depender,
							   referenced->refs, referenced->numrefs,
							   behavior);
}