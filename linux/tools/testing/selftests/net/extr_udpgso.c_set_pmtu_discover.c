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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int IPV6_MTU_DISCOVER ; 
 int IPV6_PMTUDISC_DO ; 
 int IP_MTU_DISCOVER ; 
 int IP_PMTUDISC_DO ; 
 int SOL_IP ; 
 int SOL_IPV6 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (int,int,int,int*,int) ; 

__attribute__((used)) static void set_pmtu_discover(int fd, bool is_ipv4)
{
	int level, name, val;

	if (is_ipv4) {
		level	= SOL_IP;
		name	= IP_MTU_DISCOVER;
		val	= IP_PMTUDISC_DO;
	} else {
		level	= SOL_IPV6;
		name	= IPV6_MTU_DISCOVER;
		val	= IPV6_PMTUDISC_DO;
	}

	if (setsockopt(fd, level, name, &val, sizeof(val)))
		error(1, errno, "setsockopt path mtu");
}