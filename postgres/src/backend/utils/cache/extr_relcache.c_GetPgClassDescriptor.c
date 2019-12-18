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
typedef  int /*<<< orphan*/ * TupleDesc ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildHardcodedDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Desc_pg_class ; 
 int /*<<< orphan*/  Natts_pg_class ; 

__attribute__((used)) static TupleDesc
GetPgClassDescriptor(void)
{
	static TupleDesc pgclassdesc = NULL;

	/* Already done? */
	if (pgclassdesc == NULL)
		pgclassdesc = BuildHardcodedDescriptor(Natts_pg_class,
											   Desc_pg_class);

	return pgclassdesc;
}