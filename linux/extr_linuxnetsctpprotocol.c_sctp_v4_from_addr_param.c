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
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_3__ addr; } ;
union sctp_addr_param {TYPE_4__ v4; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_2__ v4; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void sctp_v4_from_addr_param(union sctp_addr *addr,
				    union sctp_addr_param *param,
				    __be16 port, int iif)
{
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_port = port;
	addr->v4.sin_addr.s_addr = param->v4.addr.s_addr;
}