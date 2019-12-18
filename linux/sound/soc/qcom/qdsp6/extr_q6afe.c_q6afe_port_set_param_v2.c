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
typedef  int /*<<< orphan*/  u16 ;
struct q6afe_port {int /*<<< orphan*/  token; int /*<<< orphan*/  id; struct q6afe* afe; } ;
struct q6afe {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int pkt_size; int /*<<< orphan*/  opcode; int /*<<< orphan*/  token; scalar_t__ dest_port; scalar_t__ src_port; int /*<<< orphan*/  hdr_field; } ;
struct apr_pkt {TYPE_1__ hdr; } ;
struct afe_port_param_data_v2 {int module_id; int param_id; int param_size; } ;
struct afe_port_cmd_set_param_v2 {int payload_size; int payload_address_lsw; int payload_address_msw; int mem_map_handle; int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_PORT_CMD_SET_PARAM_V2 ; 
 int /*<<< orphan*/  APR_HDR_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_HDR_LEN (int) ; 
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  APR_MSG_TYPE_SEQ_CMD ; 
 int /*<<< orphan*/  APR_PKT_VER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int afe_apr_send_pkt (struct q6afe*,struct apr_pkt*,struct q6afe_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static int q6afe_port_set_param_v2(struct q6afe_port *port, void *data,
				   int param_id, int module_id, int psize)
{
	struct afe_port_cmd_set_param_v2 *param;
	struct afe_port_param_data_v2 *pdata;
	struct q6afe *afe = port->afe;
	struct apr_pkt *pkt;
	u16 port_id = port->id;
	int ret, pkt_size;
	void *p, *pl;

	pkt_size = APR_HDR_SIZE + sizeof(*param) + sizeof(*pdata) + psize;
	p = kzalloc(pkt_size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	pkt = p;
	param = p + APR_HDR_SIZE;
	pdata = p + APR_HDR_SIZE + sizeof(*param);
	pl = p + APR_HDR_SIZE + sizeof(*param) + sizeof(*pdata);
	memcpy(pl, data, psize);

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = port->token;
	pkt->hdr.opcode = AFE_PORT_CMD_SET_PARAM_V2;

	param->port_id = port_id;
	param->payload_size = sizeof(*pdata) + psize;
	param->payload_address_lsw = 0x00;
	param->payload_address_msw = 0x00;
	param->mem_map_handle = 0x00;
	pdata->module_id = module_id;
	pdata->param_id = param_id;
	pdata->param_size = psize;

	ret = afe_apr_send_pkt(afe, pkt, port);
	if (ret)
		dev_err(afe->dev, "AFE enable for port 0x%x failed %d\n",
		       port_id, ret);

	kfree(pkt);
	return ret;
}