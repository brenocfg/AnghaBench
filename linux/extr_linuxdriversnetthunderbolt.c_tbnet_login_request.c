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
struct thunderbolt_ip_login_response {int dummy; } ;
struct thunderbolt_ip_login {int /*<<< orphan*/  transmit_path; int /*<<< orphan*/  proto_version; int /*<<< orphan*/  hdr; } ;
struct tbnet {int /*<<< orphan*/  command_id; struct tb_xdomain* xd; } ;
struct tb_xdomain {int /*<<< orphan*/  remote_uuid; int /*<<< orphan*/  local_uuid; int /*<<< orphan*/  route; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  TBIP_LOGIN ; 
 int /*<<< orphan*/  TBIP_LOGIN_PROTO_VERSION ; 
 int /*<<< orphan*/  TBNET_LOCAL_PATH ; 
 int /*<<< orphan*/  TBNET_LOGIN_TIMEOUT ; 
 int /*<<< orphan*/  TB_CFG_PKG_XDOMAIN_RESP ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct thunderbolt_ip_login*,int /*<<< orphan*/ ,int) ; 
 int tb_xdomain_request (struct tb_xdomain*,struct thunderbolt_ip_login*,int,int /*<<< orphan*/ ,struct thunderbolt_ip_login_response*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbnet_fill_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tbnet_login_request(struct tbnet *net, u8 sequence)
{
	struct thunderbolt_ip_login_response reply;
	struct thunderbolt_ip_login request;
	struct tb_xdomain *xd = net->xd;

	memset(&request, 0, sizeof(request));
	tbnet_fill_header(&request.hdr, xd->route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGIN, sizeof(request),
			  atomic_inc_return(&net->command_id));

	request.proto_version = TBIP_LOGIN_PROTO_VERSION;
	request.transmit_path = TBNET_LOCAL_PATH;

	return tb_xdomain_request(xd, &request, sizeof(request),
				  TB_CFG_PKG_XDOMAIN_RESP, &reply,
				  sizeof(reply), TB_CFG_PKG_XDOMAIN_RESP,
				  TBNET_LOGIN_TIMEOUT);
}