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
typedef  int u64 ;
typedef  scalar_t__ const u32 ;
struct sock {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ const INET_DIAG_NOCOOKIE ; 
 int sock_gen_cookie (struct sock*) ; 

int sock_diag_check_cookie(struct sock *sk, const __u32 *cookie)
{
	u64 res;

	if (cookie[0] == INET_DIAG_NOCOOKIE && cookie[1] == INET_DIAG_NOCOOKIE)
		return 0;

	res = sock_gen_cookie(sk);
	if ((u32)res != cookie[0] || (u32)(res >> 32) != cookie[1])
		return -ESTALE;

	return 0;
}