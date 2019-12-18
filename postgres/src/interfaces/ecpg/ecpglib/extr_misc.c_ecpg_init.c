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
struct sqlca_t {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_NO_CONN ; 
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_CONNECTION_DOES_NOT_EXIST ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 char const* ecpg_gettext (char*) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_raise (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

bool
ecpg_init(const struct connection *con, const char *connection_name, const int lineno)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_raise(lineno, ECPG_OUT_OF_MEMORY, ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY,
				   NULL);
		return false;
	}

	ecpg_init_sqlca(sqlca);
	if (con == NULL)
	{
		ecpg_raise(lineno, ECPG_NO_CONN, ECPG_SQLSTATE_CONNECTION_DOES_NOT_EXIST,
				   connection_name ? connection_name : ecpg_gettext("NULL"));
		return false;
	}

	return true;
}