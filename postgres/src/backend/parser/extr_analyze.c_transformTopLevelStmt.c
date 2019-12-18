#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  stmt_len; int /*<<< orphan*/  stmt_location; } ;
struct TYPE_6__ {int /*<<< orphan*/  stmt_len; int /*<<< orphan*/  stmt_location; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_1__ RawStmt ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 TYPE_2__* transformOptionalSelectInto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Query *
transformTopLevelStmt(ParseState *pstate, RawStmt *parseTree)
{
	Query	   *result;

	/* We're at top level, so allow SELECT INTO */
	result = transformOptionalSelectInto(pstate, parseTree->stmt);

	result->stmt_location = parseTree->stmt_location;
	result->stmt_len = parseTree->stmt_len;

	return result;
}