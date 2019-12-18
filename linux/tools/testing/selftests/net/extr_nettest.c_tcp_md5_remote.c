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
struct sock_args {int version; int /*<<< orphan*/  password; TYPE_1__ remote_addr; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  exit (int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 scalar_t__ tcp_md5sig (int,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_md5_remote(int sd, struct sock_args *args)
{
	struct sockaddr_in sin = {
		.sin_family = AF_INET,
	};
	struct sockaddr_in6 sin6 = {
		.sin6_family = AF_INET6,
	};
	void *addr;
	int alen;

	switch (args->version) {
	case AF_INET:
		sin.sin_port = htons(args->port);
		sin.sin_addr = args->remote_addr.in;
		addr = &sin;
		alen = sizeof(sin);
		break;
	case AF_INET6:
		sin6.sin6_port = htons(args->port);
		sin6.sin6_addr = args->remote_addr.in6;
		addr = &sin6;
		alen = sizeof(sin6);
		break;
	default:
		log_error("unknown address family\n");
		exit(1);
	}

	if (tcp_md5sig(sd, addr, alen, args->password))
		return -1;

	return 0;
}