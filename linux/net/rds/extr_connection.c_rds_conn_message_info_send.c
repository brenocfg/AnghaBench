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
struct socket {int dummy; } ;
struct rds_info_lengths {int dummy; } ;
struct rds_info_iterator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_conn_message_info (struct socket*,unsigned int,struct rds_info_iterator*,struct rds_info_lengths*,int) ; 

__attribute__((used)) static void rds_conn_message_info_send(struct socket *sock, unsigned int len,
				       struct rds_info_iterator *iter,
				       struct rds_info_lengths *lens)
{
	rds_conn_message_info(sock, len, iter, lens, 1);
}