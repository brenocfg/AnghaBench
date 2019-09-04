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
struct sock {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {int sysctl_tcp_fastopen; } ;
struct TYPE_6__ {TYPE_1__ ipv4; } ;
struct TYPE_5__ {scalar_t__ fastopen_no_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_FASTOPEN_NO_COOKIE ; 
 scalar_t__ dst_metric (struct dst_entry const*,int /*<<< orphan*/ ) ; 
 TYPE_3__* sock_net (struct sock const*) ; 
 TYPE_2__* tcp_sk (struct sock const*) ; 

__attribute__((used)) static bool tcp_fastopen_no_cookie(const struct sock *sk,
				   const struct dst_entry *dst,
				   int flag)
{
	return (sock_net(sk)->ipv4.sysctl_tcp_fastopen & flag) ||
	       tcp_sk(sk)->fastopen_no_cookie ||
	       (dst && dst_metric(dst, RTAX_FASTOPEN_NO_COOKIE));
}