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
struct connection {char* name; struct connection* next; } ;

/* Variables and functions */
 struct connection* actual_connection ; 
 int /*<<< orphan*/  actual_connection_key ; 
 struct connection* all_connections ; 
 struct connection* pthread_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct connection *
ecpg_get_connection_nr(const char *connection_name)
{
	struct connection *ret = NULL;

	if ((connection_name == NULL) || (strcmp(connection_name, "CURRENT") == 0))
	{
#ifdef ENABLE_THREAD_SAFETY
		ret = pthread_getspecific(actual_connection_key);

		/*
		 * if no connection in TSD for this thread, get the global default
		 * connection and hope the user knows what they're doing (i.e. using
		 * their own mutex to protect that connection from concurrent accesses
		 */
		/* if !ret then  we  got the connection from TSD */
		if (NULL == ret)
			/* no TSD connection, going for global */
			ret = actual_connection;
#else
		ret = actual_connection;
#endif
	}
	else
	{
		struct connection *con;

		for (con = all_connections; con != NULL; con = con->next)
		{
			if (strcmp(connection_name, con->name) == 0)
				break;
		}
		ret = con;
	}

	return ret;
}