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
struct statement {int lineno; int prepared; struct statement* next; struct statement* command; struct statement* name; int /*<<< orphan*/  compat; struct connection* connection; struct statement* stmt; int /*<<< orphan*/ * outlist; int /*<<< orphan*/  inlist; } ;
struct prepared_statement {int lineno; int prepared; struct prepared_statement* next; struct prepared_statement* command; struct prepared_statement* name; int /*<<< orphan*/  compat; struct connection* connection; struct prepared_statement* stmt; int /*<<< orphan*/ * outlist; int /*<<< orphan*/  inlist; } ;
struct connection {struct statement* prep_stmts; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQprepare (int /*<<< orphan*/ ,char const*,struct statement*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ecpg_alloc (int,int) ; 
 int /*<<< orphan*/  ecpg_check_PQresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_free (struct statement*) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,char const*,struct statement*) ; 
 void* ecpg_strdup (char const*,int) ; 
 int /*<<< orphan*/  replace_variables (struct statement**,int) ; 

__attribute__((used)) static bool
prepare_common(int lineno, struct connection *con, const char *name, const char *variable)
{
	struct statement *stmt;
	struct prepared_statement *this;
	PGresult   *query;

	/* allocate new statement */
	this = (struct prepared_statement *) ecpg_alloc(sizeof(struct prepared_statement), lineno);
	if (!this)
		return false;

	stmt = (struct statement *) ecpg_alloc(sizeof(struct statement), lineno);
	if (!stmt)
	{
		ecpg_free(this);
		return false;
	}

	/* create statement */
	stmt->lineno = lineno;
	stmt->connection = con;
	stmt->command = ecpg_strdup(variable, lineno);
	stmt->inlist = stmt->outlist = NULL;

	/* if we have C variables in our statement replace them with '?' */
	replace_variables(&(stmt->command), lineno);

	/* add prepared statement to our list */
	this->name = ecpg_strdup(name, lineno);
	this->stmt = stmt;

	/* and finally really prepare the statement */
	query = PQprepare(stmt->connection->connection, name, stmt->command, 0, NULL);
	if (!ecpg_check_PQresult(query, stmt->lineno, stmt->connection->connection, stmt->compat))
	{
		ecpg_free(stmt->command);
		ecpg_free(this->name);
		ecpg_free(this);
		ecpg_free(stmt);
		return false;
	}

	ecpg_log("prepare_common on line %d: name %s; query: \"%s\"\n", stmt->lineno, name, stmt->command);
	PQclear(query);
	this->prepared = true;

	if (con->prep_stmts == NULL)
		this->next = NULL;
	else
		this->next = con->prep_stmts;

	con->prep_stmts = this;
	return true;
}