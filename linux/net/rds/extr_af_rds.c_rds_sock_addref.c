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
struct rds_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 

void rds_sock_addref(struct rds_sock *rs)
{
	sock_hold(rds_rs_to_sk(rs));
}