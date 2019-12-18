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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  mtu ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_MTU ; 
 int /*<<< orphan*/  IP_MTU ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static unsigned int get_path_mtu(int fd, bool is_ipv4)
{
	socklen_t vallen;
	unsigned int mtu;
	int ret;

	vallen = sizeof(mtu);
	if (is_ipv4)
		ret = getsockopt(fd, SOL_IP, IP_MTU, &mtu, &vallen);
	else
		ret = getsockopt(fd, SOL_IPV6, IPV6_MTU, &mtu, &vallen);

	if (ret)
		error(1, errno, "getsockopt mtu");


	fprintf(stderr, "path mtu (read):  %u\n", mtu);
	return mtu;
}