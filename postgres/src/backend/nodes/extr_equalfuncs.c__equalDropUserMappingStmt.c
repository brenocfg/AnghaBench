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
typedef  int /*<<< orphan*/  DropUserMappingStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  servername ; 
 int /*<<< orphan*/  user ; 

__attribute__((used)) static bool
_equalDropUserMappingStmt(const DropUserMappingStmt *a, const DropUserMappingStmt *b)
{
	COMPARE_NODE_FIELD(user);
	COMPARE_STRING_FIELD(servername);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}