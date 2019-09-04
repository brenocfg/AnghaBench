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
struct net {int dummy; } ;

/* Variables and functions */
 size_t AF_INET ; 
 size_t AF_INET6 ; 
#define  SKNLGRP_INET6_TCP_DESTROY 131 
#define  SKNLGRP_INET6_UDP_DESTROY 130 
#define  SKNLGRP_INET_TCP_DESTROY 129 
#define  SKNLGRP_INET_UDP_DESTROY 128 
 int /*<<< orphan*/ * sock_diag_handlers ; 
 int /*<<< orphan*/  sock_load_diag_module (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sock_diag_bind(struct net *net, int group)
{
	switch (group) {
	case SKNLGRP_INET_TCP_DESTROY:
	case SKNLGRP_INET_UDP_DESTROY:
		if (!sock_diag_handlers[AF_INET])
			sock_load_diag_module(AF_INET, 0);
		break;
	case SKNLGRP_INET6_TCP_DESTROY:
	case SKNLGRP_INET6_UDP_DESTROY:
		if (!sock_diag_handlers[AF_INET6])
			sock_load_diag_module(AF_INET6, 0);
		break;
	}
	return 0;
}