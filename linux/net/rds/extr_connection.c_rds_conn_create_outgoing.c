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
typedef  int /*<<< orphan*/  u8 ;
struct rds_transport {int dummy; } ;
struct rds_connection {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct rds_connection* __rds_conn_create (struct net*,struct in6_addr const*,struct in6_addr const*,struct rds_transport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

struct rds_connection *rds_conn_create_outgoing(struct net *net,
						const struct in6_addr *laddr,
						const struct in6_addr *faddr,
						struct rds_transport *trans,
						u8 tos, gfp_t gfp, int dev_if)
{
	return __rds_conn_create(net, laddr, faddr, trans, gfp, tos, 1, dev_if);
}