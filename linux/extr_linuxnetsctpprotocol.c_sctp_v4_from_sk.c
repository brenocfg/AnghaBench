#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_2__ v4; } ;
struct sock {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  inet_rcv_saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 TYPE_3__* inet_sk (struct sock*) ; 

__attribute__((used)) static void sctp_v4_from_sk(union sctp_addr *addr, struct sock *sk)
{
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_port = 0;
	addr->v4.sin_addr.s_addr = inet_sk(sk)->inet_rcv_saddr;
}