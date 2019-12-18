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
typedef  int /*<<< orphan*/  CreateTransformStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fromsql ; 
 int /*<<< orphan*/  lang ; 
 int /*<<< orphan*/  replace ; 
 int /*<<< orphan*/  tosql ; 
 int /*<<< orphan*/  type_name ; 

__attribute__((used)) static bool
_equalCreateTransformStmt(const CreateTransformStmt *a, const CreateTransformStmt *b)
{
	COMPARE_SCALAR_FIELD(replace);
	COMPARE_NODE_FIELD(type_name);
	COMPARE_STRING_FIELD(lang);
	COMPARE_NODE_FIELD(fromsql);
	COMPARE_NODE_FIELD(tosql);

	return true;
}