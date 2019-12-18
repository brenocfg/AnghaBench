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
typedef  int /*<<< orphan*/  CreatePLangStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plhandler ; 
 int /*<<< orphan*/  plinline ; 
 int /*<<< orphan*/  plname ; 
 int /*<<< orphan*/  pltrusted ; 
 int /*<<< orphan*/  plvalidator ; 
 int /*<<< orphan*/  replace ; 

__attribute__((used)) static bool
_equalCreatePLangStmt(const CreatePLangStmt *a, const CreatePLangStmt *b)
{
	COMPARE_SCALAR_FIELD(replace);
	COMPARE_STRING_FIELD(plname);
	COMPARE_NODE_FIELD(plhandler);
	COMPARE_NODE_FIELD(plinline);
	COMPARE_NODE_FIELD(plvalidator);
	COMPARE_SCALAR_FIELD(pltrusted);

	return true;
}