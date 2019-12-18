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
 int /*<<< orphan*/  ECPG_COMPAT_PGSQL ; 
 int /*<<< orphan*/  deallocate_one (int,int /*<<< orphan*/ ,struct connection*,struct prepared_statement*,struct prepared_statement*) ; 
 struct prepared_statement* ecpg_find_prepared_statement (char const*,struct connection*,struct prepared_statement**) ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int prepare_common (int,struct connection*,char const*,char const*) ; 

bool
ECPGprepare(int lineno, const char *connection_name, const bool questionmarks,
			const char *name, const char *variable)
{
	struct connection *con;
	struct prepared_statement *this,
			   *prev;

	(void) questionmarks;		/* quiet the compiler */

	con = ecpg_get_connection(connection_name);
	if (!ecpg_init(con, connection_name, lineno))
		return false;

	/* check if we already have prepared this statement */
	this = ecpg_find_prepared_statement(name, con, &prev);
	if (this && !deallocate_one(lineno, ECPG_COMPAT_PGSQL, con, prev, this))
		return false;

	return prepare_common(lineno, con, name, variable);
}