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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int sock_gen_cookie (struct sock*) ; 

void sock_diag_save_cookie(struct sock *sk, __u32 *cookie)
{
	u64 res = sock_gen_cookie(sk);

	cookie[0] = (u32)res;
	cookie[1] = (u32)(res >> 32);
}