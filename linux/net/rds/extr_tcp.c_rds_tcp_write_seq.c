#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rds_tcp_connection {TYPE_1__* t_sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 TYPE_2__* tcp_sk (int /*<<< orphan*/ ) ; 

u32 rds_tcp_write_seq(struct rds_tcp_connection *tc)
{
	/* seq# of the last byte of data in tcp send buffer */
	return tcp_sk(tc->t_sock->sk)->write_seq;
}