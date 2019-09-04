#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct TYPE_4__ {void* connection_id; } ;
struct TYPE_5__ {TYPE_1__ dgm; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct caif_connect_request {int /*<<< orphan*/  protocol; TYPE_3__ sockaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIFPROTO_DATAGRAM ; 
 int /*<<< orphan*/  CAIFPROTO_DATAGRAM_LOOP ; 
 size_t IFLA_CAIF_IPV4_CONNID ; 
 size_t IFLA_CAIF_IPV6_CONNID ; 
 size_t IFLA_CAIF_LOOPBACK ; 
 void* nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void caif_netlink_parms(struct nlattr *data[],
			       struct caif_connect_request *conn_req)
{
	if (!data) {
		pr_warn("no params data found\n");
		return;
	}
	if (data[IFLA_CAIF_IPV4_CONNID])
		conn_req->sockaddr.u.dgm.connection_id =
			nla_get_u32(data[IFLA_CAIF_IPV4_CONNID]);
	if (data[IFLA_CAIF_IPV6_CONNID])
		conn_req->sockaddr.u.dgm.connection_id =
			nla_get_u32(data[IFLA_CAIF_IPV6_CONNID]);
	if (data[IFLA_CAIF_LOOPBACK]) {
		if (nla_get_u8(data[IFLA_CAIF_LOOPBACK]))
			conn_req->protocol = CAIFPROTO_DATAGRAM_LOOP;
		else
			conn_req->protocol = CAIFPROTO_DATAGRAM;
	}
}