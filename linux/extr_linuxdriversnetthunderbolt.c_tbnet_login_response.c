#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct thunderbolt_ip_login_response {int /*<<< orphan*/  receiver_mac_len; int /*<<< orphan*/  receiver_mac; int /*<<< orphan*/  hdr; } ;
struct tbnet {TYPE_1__* dev; struct tb_xdomain* xd; } ;
struct tb_xdomain {int /*<<< orphan*/  remote_uuid; int /*<<< orphan*/  local_uuid; } ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  TBIP_LOGIN_RESPONSE ; 
 int /*<<< orphan*/  TB_CFG_PKG_XDOMAIN_RESP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct thunderbolt_ip_login_response*,int /*<<< orphan*/ ,int) ; 
 int tb_xdomain_response (struct tb_xdomain*,struct thunderbolt_ip_login_response*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbnet_fill_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tbnet_login_response(struct tbnet *net, u64 route, u8 sequence,
				u32 command_id)
{
	struct thunderbolt_ip_login_response reply;
	struct tb_xdomain *xd = net->xd;

	memset(&reply, 0, sizeof(reply));
	tbnet_fill_header(&reply.hdr, route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGIN_RESPONSE, sizeof(reply),
			  command_id);
	memcpy(reply.receiver_mac, net->dev->dev_addr, ETH_ALEN);
	reply.receiver_mac_len = ETH_ALEN;

	return tb_xdomain_response(xd, &reply, sizeof(reply),
				   TB_CFG_PKG_XDOMAIN_RESP);
}