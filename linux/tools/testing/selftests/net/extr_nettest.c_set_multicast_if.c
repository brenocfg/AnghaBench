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
struct ip_mreqn {int imr_ifindex; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_mreqn*,int) ; 

__attribute__((used)) static int set_multicast_if(int sd, int ifindex)
{
	struct ip_mreqn mreq = { .imr_ifindex = ifindex };
	int rc;

	rc = setsockopt(sd, SOL_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq));
	if (rc < 0)
		log_err_errno("setsockopt(IP_MULTICAST_IF)");

	return rc;
}