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
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_relid ; 
 int /*<<< orphan*/  child_reltype ; 
 int /*<<< orphan*/  parent_relid ; 
 int /*<<< orphan*/  parent_reloid ; 
 int /*<<< orphan*/  parent_reltype ; 
 int /*<<< orphan*/  translated_vars ; 

__attribute__((used)) static bool
_equalAppendRelInfo(const AppendRelInfo *a, const AppendRelInfo *b)
{
	COMPARE_SCALAR_FIELD(parent_relid);
	COMPARE_SCALAR_FIELD(child_relid);
	COMPARE_SCALAR_FIELD(parent_reltype);
	COMPARE_SCALAR_FIELD(child_reltype);
	COMPARE_NODE_FIELD(translated_vars);
	COMPARE_SCALAR_FIELD(parent_reloid);

	return true;
}