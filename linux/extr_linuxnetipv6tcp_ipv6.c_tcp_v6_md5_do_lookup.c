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
struct tcp_md5sig_key {int dummy; } ;
struct sock {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct tcp_md5sig_key *tcp_v6_md5_do_lookup(const struct sock *sk,
						   const struct in6_addr *addr)
{
	return NULL;
}