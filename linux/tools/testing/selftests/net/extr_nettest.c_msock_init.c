#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_3__ in; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sock_args {int /*<<< orphan*/  ifindex; TYPE_4__ local_addr; TYPE_2__ grp; scalar_t__ use_setsockopt; int /*<<< orphan*/  dev; scalar_t__ has_local_ip; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  laddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ bind_to_device (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 scalar_t__ set_membership (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ set_multicast_if (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msock_init(struct sock_args *args, int server)
{
	uint32_t if_addr = htonl(INADDR_ANY);
	struct sockaddr_in laddr = {
		.sin_family = AF_INET,
		.sin_port = htons(args->port),
	};
	int one = 1;
	int sd;

	if (!server && args->has_local_ip)
		if_addr = args->local_addr.in.s_addr;

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		log_err_errno("socket");
		return -1;
	}

	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
		       (char *)&one, sizeof(one)) < 0) {
		log_err_errno("Setting SO_REUSEADDR error");
		goto out_err;
	}

	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST,
		       (char *)&one, sizeof(one)) < 0)
		log_err_errno("Setting SO_BROADCAST error");

	if (args->dev && bind_to_device(sd, args->dev) != 0)
		goto out_err;
	else if (args->use_setsockopt &&
		 set_multicast_if(sd, args->ifindex))
		goto out_err;

	laddr.sin_addr.s_addr = if_addr;

	if (bind(sd, (struct sockaddr *) &laddr, sizeof(laddr)) < 0) {
		log_err_errno("bind failed");
		goto out_err;
	}

	if (server &&
	    set_membership(sd, args->grp.s_addr,
			   args->local_addr.in.s_addr, args->ifindex))
		goto out_err;

	return sd;
out_err:
	close(sd);
	return -1;
}