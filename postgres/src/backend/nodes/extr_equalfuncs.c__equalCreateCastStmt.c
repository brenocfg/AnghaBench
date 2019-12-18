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
typedef  int /*<<< orphan*/  CreateCastStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  inout ; 
 int /*<<< orphan*/  sourcetype ; 
 int /*<<< orphan*/  targettype ; 

__attribute__((used)) static bool
_equalCreateCastStmt(const CreateCastStmt *a, const CreateCastStmt *b)
{
	COMPARE_NODE_FIELD(sourcetype);
	COMPARE_NODE_FIELD(targettype);
	COMPARE_NODE_FIELD(func);
	COMPARE_SCALAR_FIELD(context);
	COMPARE_SCALAR_FIELD(inout);

	return true;
}