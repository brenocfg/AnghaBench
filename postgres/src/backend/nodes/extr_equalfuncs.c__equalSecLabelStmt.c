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
typedef  int /*<<< orphan*/  SecLabelStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label ; 
 int /*<<< orphan*/  object ; 
 int /*<<< orphan*/  objtype ; 
 int /*<<< orphan*/  provider ; 

__attribute__((used)) static bool
_equalSecLabelStmt(const SecLabelStmt *a, const SecLabelStmt *b)
{
	COMPARE_SCALAR_FIELD(objtype);
	COMPARE_NODE_FIELD(object);
	COMPARE_STRING_FIELD(provider);
	COMPARE_STRING_FIELD(label);

	return true;
}