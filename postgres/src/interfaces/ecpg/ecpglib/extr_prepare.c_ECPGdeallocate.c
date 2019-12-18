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
struct prepared_statement {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_INVALID_STMT ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_INVALID_SQL_STATEMENT_NAME ; 
 scalar_t__ INFORMIX_MODE (int) ; 
 int deallocate_one (int,int,struct connection*,struct prepared_statement*,struct prepared_statement*) ; 
 struct prepared_statement* ecpg_find_prepared_statement (char const*,struct connection*,struct prepared_statement**) ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

bool
ECPGdeallocate(int lineno, int c, const char *connection_name, const char *name)
{
	struct connection *con;
	struct prepared_statement *this,
			   *prev;

	con = ecpg_get_connection(connection_name);
	if (!ecpg_init(con, connection_name, lineno))
		return false;

	this = ecpg_find_prepared_statement(name, con, &prev);
	if (this)
		return deallocate_one(lineno, c, con, prev, this);

	/* prepared statement is not found */
	if (INFORMIX_MODE(c))
		return true;
	ecpg_raise(lineno, ECPG_INVALID_STMT, ECPG_SQLSTATE_INVALID_SQL_STATEMENT_NAME, name);
	return false;
}