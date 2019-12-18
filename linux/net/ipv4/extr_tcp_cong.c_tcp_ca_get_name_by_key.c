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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_congestion_ops {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CA_NAME_MAX ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 char* strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_congestion_ops* tcp_ca_find_key (int /*<<< orphan*/ ) ; 

char *tcp_ca_get_name_by_key(u32 key, char *buffer)
{
	const struct tcp_congestion_ops *ca;
	char *ret = NULL;

	rcu_read_lock();
	ca = tcp_ca_find_key(key);
	if (ca)
		ret = strncpy(buffer, ca->name,
			      TCP_CA_NAME_MAX);
	rcu_read_unlock();

	return ret;
}