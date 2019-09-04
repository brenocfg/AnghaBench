#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rndis_params {int /*<<< orphan*/  v; int /*<<< orphan*/  (* resp_avail ) (int /*<<< orphan*/ ) ;TYPE_1__* dev; } ;
struct rndis_packet_msg_type {int dummy; } ;
struct ethhdr {int dummy; } ;
struct TYPE_8__ {scalar_t__ buf; } ;
typedef  TYPE_2__ rndis_resp_t ;
struct TYPE_9__ {int /*<<< orphan*/  RequestID; } ;
typedef  TYPE_3__ rndis_init_msg_type ;
struct TYPE_10__ {void* AFListSize; void* AFListOffset; void* PacketAlignmentFactor; void* MaxTransferSize; void* MaxPacketsPerTransfer; void* Medium; void* DeviceFlags; void* MinorVersion; void* MajorVersion; void* Status; int /*<<< orphan*/  RequestID; void* MessageLength; void* MessageType; } ;
typedef  TYPE_4__ rndis_init_cmplt_type ;
struct TYPE_7__ {int mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int RNDIS_DF_CONNECTIONLESS ; 
 int RNDIS_MAJOR_VERSION ; 
 int RNDIS_MEDIUM_802_3 ; 
 int RNDIS_MINOR_VERSION ; 
 int RNDIS_MSG_INIT_C ; 
 int RNDIS_STATUS_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 TYPE_2__* rndis_add_response (struct rndis_params*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_init_response(struct rndis_params *params,
			       rndis_init_msg_type *buf)
{
	rndis_init_cmplt_type *resp;
	rndis_resp_t *r;

	if (!params->dev)
		return -ENOTSUPP;

	r = rndis_add_response(params, sizeof(rndis_init_cmplt_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_init_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_INIT_C);
	resp->MessageLength = cpu_to_le32(52);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);
	resp->MajorVersion = cpu_to_le32(RNDIS_MAJOR_VERSION);
	resp->MinorVersion = cpu_to_le32(RNDIS_MINOR_VERSION);
	resp->DeviceFlags = cpu_to_le32(RNDIS_DF_CONNECTIONLESS);
	resp->Medium = cpu_to_le32(RNDIS_MEDIUM_802_3);
	resp->MaxPacketsPerTransfer = cpu_to_le32(1);
	resp->MaxTransferSize = cpu_to_le32(
		  params->dev->mtu
		+ sizeof(struct ethhdr)
		+ sizeof(struct rndis_packet_msg_type)
		+ 22);
	resp->PacketAlignmentFactor = cpu_to_le32(0);
	resp->AFListOffset = cpu_to_le32(0);
	resp->AFListSize = cpu_to_le32(0);

	params->resp_avail(params->v);
	return 0;
}