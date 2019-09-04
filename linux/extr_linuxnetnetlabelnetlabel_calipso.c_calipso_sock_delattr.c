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
struct netlbl_calipso_ops {int /*<<< orphan*/  (* sock_delattr ) (struct sock*) ;} ;

/* Variables and functions */
 struct netlbl_calipso_ops* netlbl_calipso_ops_get () ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void calipso_sock_delattr(struct sock *sk)
{
	const struct netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	if (ops)
		ops->sock_delattr(sk);
}