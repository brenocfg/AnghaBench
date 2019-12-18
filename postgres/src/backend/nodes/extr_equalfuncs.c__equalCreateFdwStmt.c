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
typedef  int /*<<< orphan*/  CreateFdwStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdwname ; 
 int /*<<< orphan*/  func_options ; 
 int /*<<< orphan*/  options ; 

__attribute__((used)) static bool
_equalCreateFdwStmt(const CreateFdwStmt *a, const CreateFdwStmt *b)
{
	COMPARE_STRING_FIELD(fdwname);
	COMPARE_NODE_FIELD(func_options);
	COMPARE_NODE_FIELD(options);

	return true;
}