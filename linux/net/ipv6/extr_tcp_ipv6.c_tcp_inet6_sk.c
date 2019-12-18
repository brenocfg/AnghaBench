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
typedef  int /*<<< orphan*/  u8 ;
struct tcp6_sock {int dummy; } ;
struct sock {int dummy; } ;
struct ipv6_pinfo {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ipv6_pinfo *tcp_inet6_sk(const struct sock *sk)
{
	unsigned int offset = sizeof(struct tcp6_sock) - sizeof(struct ipv6_pinfo);

	return (struct ipv6_pinfo *)(((u8 *)sk) + offset);
}