#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int curvar; TYPE_1__* target; int /*<<< orphan*/  is_move; } ;
struct TYPE_5__ {int dno; char* refname; } ;
typedef  TYPE_2__ PLpgSQL_stmt_fetch ;

/* Variables and functions */
 int /*<<< orphan*/  dump_cursor_direction (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int dump_indent ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
dump_fetch(PLpgSQL_stmt_fetch *stmt)
{
	dump_ind();

	if (!stmt->is_move)
	{
		printf("FETCH curvar=%d\n", stmt->curvar);
		dump_cursor_direction(stmt);

		dump_indent += 2;
		if (stmt->target != NULL)
		{
			dump_ind();
			printf("    target = %d %s\n",
				   stmt->target->dno, stmt->target->refname);
		}
		dump_indent -= 2;
	}
	else
	{
		printf("MOVE curvar=%d\n", stmt->curvar);
		dump_cursor_direction(stmt);
	}
}