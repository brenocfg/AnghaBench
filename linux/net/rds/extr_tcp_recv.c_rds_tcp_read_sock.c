#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct rds_tcp_desc_arg {int /*<<< orphan*/  gfp; struct rds_conn_path* conn_path; } ;
struct rds_tcp_connection {struct socket* t_sock; } ;
struct rds_conn_path {struct rds_tcp_connection* cp_transport_data; } ;
struct TYPE_4__ {struct rds_tcp_desc_arg* data; } ;
struct TYPE_5__ {int error; int count; TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  rds_tcp_data_recv ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_tcp_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_read_sock (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rds_tcp_read_sock(struct rds_conn_path *cp, gfp_t gfp)
{
	struct rds_tcp_connection *tc = cp->cp_transport_data;
	struct socket *sock = tc->t_sock;
	read_descriptor_t desc;
	struct rds_tcp_desc_arg arg;

	/* It's like glib in the kernel! */
	arg.conn_path = cp;
	arg.gfp = gfp;
	desc.arg.data = &arg;
	desc.error = 0;
	desc.count = 1; /* give more than one skb per call */

	tcp_read_sock(sock->sk, &desc, rds_tcp_data_recv);
	rdsdebug("tcp_read_sock for tc %p gfp 0x%x returned %d\n", tc, gfp,
		 desc.error);

	return desc.error;
}