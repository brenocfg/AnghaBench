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
typedef  int /*<<< orphan*/  Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_FIXED_PART_SIZE ; 
 int /*<<< orphan*/  MemoryContextAllocZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 

__attribute__((used)) static Form_pg_attribute
AllocateAttribute(void)
{
	return (Form_pg_attribute)
		MemoryContextAllocZero(TopMemoryContext, ATTRIBUTE_FIXED_PART_SIZE);
}