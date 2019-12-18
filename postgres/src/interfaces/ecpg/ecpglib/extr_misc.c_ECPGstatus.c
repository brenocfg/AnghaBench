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
struct connection {int /*<<< orphan*/  name; int /*<<< orphan*/ * connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_NOT_CONN ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_INTERNAL_ERROR ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ECPGstatus(int lineno, const char *connection_name)
{
	struct connection *con = ecpg_get_connection(connection_name);

	if (!ecpg_init(con, connection_name, lineno))
		return false;

	/* are we connected? */
	if (con->connection == NULL)
	{
		ecpg_raise(lineno, ECPG_NOT_CONN, ECPG_SQLSTATE_ECPG_INTERNAL_ERROR, con->name);
		return false;
	}

	return true;
}