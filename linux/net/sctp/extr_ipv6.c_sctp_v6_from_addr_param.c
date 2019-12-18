#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
union sctp_addr_param {TYPE_2__ v6; } ;
struct TYPE_3__ {int sin6_scope_id; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sctp_addr {TYPE_1__ v6; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 

__attribute__((used)) static void sctp_v6_from_addr_param(union sctp_addr *addr,
				    union sctp_addr_param *param,
				    __be16 port, int iif)
{
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = port;
	addr->v6.sin6_flowinfo = 0; /* BUG */
	addr->v6.sin6_addr = param->v6.addr;
	addr->v6.sin6_scope_id = iif;
}