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
typedef  int /*<<< orphan*/  CreateFunctionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funcname ; 
 int /*<<< orphan*/  is_procedure ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  parameters ; 
 int /*<<< orphan*/  replace ; 
 int /*<<< orphan*/  returnType ; 

__attribute__((used)) static bool
_equalCreateFunctionStmt(const CreateFunctionStmt *a, const CreateFunctionStmt *b)
{
	COMPARE_SCALAR_FIELD(is_procedure);
	COMPARE_SCALAR_FIELD(replace);
	COMPARE_NODE_FIELD(funcname);
	COMPARE_NODE_FIELD(parameters);
	COMPARE_NODE_FIELD(returnType);
	COMPARE_NODE_FIELD(options);

	return true;
}