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

/* Variables and functions */
 int ecpg_deallocate_all_conn (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_get_connection (char const*) ; 

bool
ECPGdeallocate_all(int lineno, int compat, const char *connection_name)
{
	return ecpg_deallocate_all_conn(lineno, compat,
									ecpg_get_connection(connection_name));
}