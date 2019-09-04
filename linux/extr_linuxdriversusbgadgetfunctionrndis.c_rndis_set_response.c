#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rndis_params {int /*<<< orphan*/  v; int /*<<< orphan*/  (* resp_avail ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  OID; int /*<<< orphan*/  RequestID; int /*<<< orphan*/  InformationBufferOffset; int /*<<< orphan*/  InformationBufferLength; } ;
typedef  TYPE_1__ rndis_set_msg_type ;
struct TYPE_8__ {void* Status; int /*<<< orphan*/  RequestID; void* MessageLength; void* MessageType; } ;
typedef  TYPE_2__ rndis_set_cmplt_type ;
struct TYPE_9__ {scalar_t__ buf; } ;
typedef  TYPE_3__ rndis_resp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int RNDIS_MSG_SET_C ; 
 int RNDIS_STATUS_NOT_SUPPORTED ; 
 int RNDIS_STATUS_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ gen_ndis_set_resp (struct rndis_params*,int,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__* rndis_add_response (struct rndis_params*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_set_response(struct rndis_params *params,
			      rndis_set_msg_type *buf)
{
	u32 BufLength, BufOffset;
	rndis_set_cmplt_type *resp;
	rndis_resp_t *r;

	r = rndis_add_response(params, sizeof(rndis_set_cmplt_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_set_cmplt_type *)r->buf;

	BufLength = le32_to_cpu(buf->InformationBufferLength);
	BufOffset = le32_to_cpu(buf->InformationBufferOffset);

#ifdef	VERBOSE_DEBUG
	pr_debug("%s: Length: %d\n", __func__, BufLength);
	pr_debug("%s: Offset: %d\n", __func__, BufOffset);
	pr_debug("%s: InfoBuffer: ", __func__);

	for (i = 0; i < BufLength; i++) {
		pr_debug("%02x ", *(((u8 *) buf) + i + 8 + BufOffset));
	}

	pr_debug("\n");
#endif

	resp->MessageType = cpu_to_le32(RNDIS_MSG_SET_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	if (gen_ndis_set_resp(params, le32_to_cpu(buf->OID),
			((u8 *)buf) + 8 + BufOffset, BufLength, r))
		resp->Status = cpu_to_le32(RNDIS_STATUS_NOT_SUPPORTED);
	else
		resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	return 0;
}