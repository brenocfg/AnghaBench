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
struct TYPE_6__ {int /*<<< orphan*/  stats; int /*<<< orphan*/ * expr; int /*<<< orphan*/ * varprefix; int /*<<< orphan*/  argv; scalar_t__ argc; int /*<<< orphan*/  meta; int /*<<< orphan*/  type; int /*<<< orphan*/ * first_line; int /*<<< orphan*/  lines; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  TYPE_2__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  META_NONE ; 
 int /*<<< orphan*/  SQL_COMMAND ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initSimpleStats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pg_malloc (int) ; 
 char* skip_sql_comments (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Command *
create_sql_command(PQExpBuffer buf, const char *source)
{
	Command    *my_command;
	char	   *p = skip_sql_comments(buf->data);

	if (p == NULL)
		return NULL;

	/* Allocate and initialize Command structure */
	my_command = (Command *) pg_malloc(sizeof(Command));
	initPQExpBuffer(&my_command->lines);
	appendPQExpBufferStr(&my_command->lines, p);
	my_command->first_line = NULL;	/* this is set later */
	my_command->type = SQL_COMMAND;
	my_command->meta = META_NONE;
	my_command->argc = 0;
	memset(my_command->argv, 0, sizeof(my_command->argv));
	my_command->varprefix = NULL;	/* allocated later, if needed */
	my_command->expr = NULL;
	initSimpleStats(&my_command->stats);

	return my_command;
}