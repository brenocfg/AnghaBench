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
typedef  scalar_t__ TuplesortSpaceType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ SORT_SPACE_TYPE_DISK ; 
 scalar_t__ SORT_SPACE_TYPE_MEMORY ; 

const char *
tuplesort_space_type_name(TuplesortSpaceType t)
{
	Assert(t == SORT_SPACE_TYPE_DISK || t == SORT_SPACE_TYPE_MEMORY);
	return t == SORT_SPACE_TYPE_DISK ? "Disk" : "Memory";
}