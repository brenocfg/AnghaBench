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
struct connection {struct connection* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 struct connection* all_connections ; 
 int /*<<< orphan*/  connections_mutex ; 
 int /*<<< orphan*/  ecpg_finish (struct connection*) ; 
 struct connection* ecpg_get_connection_nr (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

bool
ECPGdisconnect(int lineno, const char *connection_name)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();
	struct connection *con;

	if (sqlca == NULL)
	{
		ecpg_raise(lineno, ECPG_OUT_OF_MEMORY,
				   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}

#ifdef ENABLE_THREAD_SAFETY
	pthread_mutex_lock(&connections_mutex);
#endif

	if (strcmp(connection_name, "ALL") == 0)
	{
		ecpg_init_sqlca(sqlca);
		for (con = all_connections; con;)
		{
			struct connection *f = con;

			con = con->next;
			ecpg_finish(f);
		}
	}
	else
	{
		con = ecpg_get_connection_nr(connection_name);

		if (!ecpg_init(con, connection_name, lineno))
		{
#ifdef ENABLE_THREAD_SAFETY
			pthread_mutex_unlock(&connections_mutex);
#endif
			return false;
		}
		else
			ecpg_finish(con);
	}

#ifdef ENABLE_THREAD_SAFETY
	pthread_mutex_unlock(&connections_mutex);
#endif

	return true;
}