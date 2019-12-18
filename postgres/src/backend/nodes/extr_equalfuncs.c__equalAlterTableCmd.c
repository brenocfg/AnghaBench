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
typedef  int /*<<< orphan*/  AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  def ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  newowner ; 
 int /*<<< orphan*/  num ; 
 int /*<<< orphan*/  subtype ; 

__attribute__((used)) static bool
_equalAlterTableCmd(const AlterTableCmd *a, const AlterTableCmd *b)
{
	COMPARE_SCALAR_FIELD(subtype);
	COMPARE_STRING_FIELD(name);
	COMPARE_SCALAR_FIELD(num);
	COMPARE_NODE_FIELD(newowner);
	COMPARE_NODE_FIELD(def);
	COMPARE_SCALAR_FIELD(behavior);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}