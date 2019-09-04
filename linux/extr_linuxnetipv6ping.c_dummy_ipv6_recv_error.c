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
struct sock {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 

__attribute__((used)) static int dummy_ipv6_recv_error(struct sock *sk, struct msghdr *msg, int len,
				 int *addr_len)
{
	return -EAFNOSUPPORT;
}