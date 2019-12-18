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
struct statement {int lineno; void* name; int /*<<< orphan*/ * outlist; int /*<<< orphan*/  inlist; void* command; struct connection* connection; } ;
struct prepared_statement {int prepared; struct prepared_statement* next; struct statement* stmt; void* name; } ;
struct connection {struct prepared_statement* prep_stmts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_COMPAT_PGSQL ; 
 int /*<<< orphan*/  deallocate_one (int,int /*<<< orphan*/ ,struct connection*,struct prepared_statement*,struct prepared_statement*) ; 
 scalar_t__ ecpg_alloc (int,int) ; 
 struct prepared_statement* ecpg_find_prepared_statement (void*,struct connection*,struct prepared_statement**) ; 
 int /*<<< orphan*/  ecpg_free (struct prepared_statement*) ; 
 void* ecpg_strdup (void*,int) ; 
 int /*<<< orphan*/  memset (struct statement*,int /*<<< orphan*/ ,int) ; 

bool
ecpg_register_prepared_stmt(struct statement *stmt)
{
	struct statement *prep_stmt;
	struct prepared_statement *this;
	struct connection *con = stmt->connection;
	struct prepared_statement *prev = NULL;
	int			lineno = stmt->lineno;

	/* check if we already have prepared this statement */
	this = ecpg_find_prepared_statement(stmt->name, con, &prev);
	if (this && !deallocate_one(lineno, ECPG_COMPAT_PGSQL, con, prev, this))
		return false;

	/* allocate new statement */
	this = (struct prepared_statement *) ecpg_alloc(sizeof(struct prepared_statement), lineno);
	if (!this)
		return false;

	prep_stmt = (struct statement *) ecpg_alloc(sizeof(struct statement), lineno);
	if (!prep_stmt)
	{
		ecpg_free(this);
		return false;
	}
	memset(prep_stmt, 0, sizeof(struct statement));

	/* create statement */
	prep_stmt->lineno = lineno;
	prep_stmt->connection = con;
	prep_stmt->command = ecpg_strdup(stmt->command, lineno);
	prep_stmt->inlist = prep_stmt->outlist = NULL;
	this->name = ecpg_strdup(stmt->name, lineno);
	this->stmt = prep_stmt;
	this->prepared = true;

	if (con->prep_stmts == NULL)
		this->next = NULL;
	else
		this->next = con->prep_stmts;

	con->prep_stmts = this;
	return true;
}