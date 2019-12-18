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
typedef  int /*<<< orphan*/  AlterDomainStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  def ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  subtype ; 
 int /*<<< orphan*/  typeName ; 

__attribute__((used)) static bool
_equalAlterDomainStmt(const AlterDomainStmt *a, const AlterDomainStmt *b)
{
	COMPARE_SCALAR_FIELD(subtype);
	COMPARE_NODE_FIELD(typeName);
	COMPARE_STRING_FIELD(name);
	COMPARE_NODE_FIELD(def);
	COMPARE_SCALAR_FIELD(behavior);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}