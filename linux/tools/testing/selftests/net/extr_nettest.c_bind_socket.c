#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_addr; void* sin6_port; } ;
struct sockaddr_in {int sin_family; int /*<<< orphan*/  sin_addr; void* sin_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct sock_args {scalar_t__ type; int version; TYPE_1__ local_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  has_local_ip; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  serv_addr ;
typedef  int /*<<< orphan*/  serv6_addr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ bind (int,void*,int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_error (char*) ; 

__attribute__((used)) static int bind_socket(int sd, struct sock_args *args)
{
	struct sockaddr_in serv_addr = {
		.sin_family = AF_INET,
	};
	struct sockaddr_in6 serv6_addr = {
		.sin6_family = AF_INET6,
	};
	void *addr;
	socklen_t alen;

	if (!args->has_local_ip && args->type == SOCK_RAW)
		return 0;

	switch (args->version) {
	case AF_INET:
		serv_addr.sin_port = htons(args->port);
		serv_addr.sin_addr = args->local_addr.in;
		addr = &serv_addr;
		alen = sizeof(serv_addr);
		break;

	case AF_INET6:
		serv6_addr.sin6_port = htons(args->port);
		serv6_addr.sin6_addr = args->local_addr.in6;
		addr = &serv6_addr;
		alen = sizeof(serv6_addr);
		break;

	default:
		log_error("Invalid address family\n");
		return -1;
	}

	if (bind(sd, addr, alen) < 0) {
		log_err_errno("error binding socket");
		return -1;
	}

	return 0;
}