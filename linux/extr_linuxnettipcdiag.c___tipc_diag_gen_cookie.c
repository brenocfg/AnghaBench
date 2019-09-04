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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_diag_save_cookie (struct sock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 __tipc_diag_gen_cookie(struct sock *sk)
{
	u32 res[2];

	sock_diag_save_cookie(sk, res);
	return *((u64 *)res);
}