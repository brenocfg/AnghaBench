#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_1__ RawStmt ;

/* Variables and functions */
#define  T_CreateTableAsStmt 134 
#define  T_DeclareCursorStmt 133 
#define  T_DeleteStmt 132 
#define  T_ExplainStmt 131 
#define  T_InsertStmt 130 
#define  T_SelectStmt 129 
#define  T_UpdateStmt 128 
 int nodeTag (int /*<<< orphan*/ ) ; 

bool
analyze_requires_snapshot(RawStmt *parseTree)
{
	bool		result;

	switch (nodeTag(parseTree->stmt))
	{
			/*
			 * Optimizable statements
			 */
		case T_InsertStmt:
		case T_DeleteStmt:
		case T_UpdateStmt:
		case T_SelectStmt:
			result = true;
			break;

			/*
			 * Special cases
			 */
		case T_DeclareCursorStmt:
		case T_ExplainStmt:
		case T_CreateTableAsStmt:
			/* yes, because we must analyze the contained statement */
			result = true;
			break;

		default:
			/* other utility statements don't have any real parse analysis */
			result = false;
			break;
	}

	return result;
}