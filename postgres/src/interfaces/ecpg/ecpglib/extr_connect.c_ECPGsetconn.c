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
struct connection {int dummy; } ;

/* Variables and functions */
 struct connection* actual_connection ; 
 int /*<<< orphan*/  actual_connection_key ; 
 struct connection* ecpg_get_connection (char const*) ; 
 int /*<<< orphan*/  ecpg_init (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct connection*) ; 

bool
ECPGsetconn(int lineno, const char *connection_name)
{
	struct connection *con = ecpg_get_connection(connection_name);

	if (!ecpg_init(con, connection_name, lineno))
		return false;

#ifdef ENABLE_THREAD_SAFETY
	pthread_setspecific(actual_connection_key, con);
#else
	actual_connection = con;
#endif
	return true;
}