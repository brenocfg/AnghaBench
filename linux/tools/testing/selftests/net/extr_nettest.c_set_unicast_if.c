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
typedef  int /*<<< orphan*/  ifindex ;

/* Variables and functions */
 int AF_INET6 ; 
 int IPV6_UNICAST_IF ; 
 int IP_UNICAST_IF ; 
 int SOL_IP ; 
 int SOL_IPV6 ; 
 int htonl (int) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int setsockopt (int,int,int,int*,int) ; 

__attribute__((used)) static int set_unicast_if(int sd, int ifindex, int version)
{
	int opt = IP_UNICAST_IF;
	int level = SOL_IP;
	int rc;

	ifindex = htonl(ifindex);

	if (version == AF_INET6) {
		opt = IPV6_UNICAST_IF;
		level = SOL_IPV6;
	}
	rc = setsockopt(sd, level, opt, &ifindex, sizeof(ifindex));
	if (rc < 0)
		log_err_errno("setsockopt(IP_UNICAST_IF)");

	return rc;
}