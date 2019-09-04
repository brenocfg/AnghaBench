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
struct q6core {int resp_received; int /*<<< orphan*/  fwk_version_supported; int /*<<< orphan*/  wait; struct apr_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  pkt_size; int /*<<< orphan*/  hdr_field; } ;
struct apr_pkt {TYPE_1__ hdr; } ;
struct apr_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HDR_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_HDR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_HDR_SIZE ; 
 int /*<<< orphan*/  APR_MSG_TYPE_SEQ_CMD ; 
 int /*<<< orphan*/  APR_PKT_VER ; 
 int /*<<< orphan*/  AVCS_CMD_GET_FWK_VERSION ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  Q6_READY_TIMEOUT_MS ; 
 int apr_send_pkt (struct apr_device*,struct apr_pkt*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6core_get_fwk_versions(struct q6core *core)
{
	struct apr_device *adev = core->adev;
	struct apr_pkt pkt;
	int rc;

	pkt.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
				      APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
	pkt.hdr.pkt_size = APR_HDR_SIZE;
	pkt.hdr.opcode = AVCS_CMD_GET_FWK_VERSION;

	rc = apr_send_pkt(adev, &pkt);
	if (rc < 0)
		return rc;

	rc = wait_event_timeout(core->wait, (core->resp_received),
				msecs_to_jiffies(Q6_READY_TIMEOUT_MS));
	if (rc > 0 && core->resp_received) {
		core->resp_received = false;

		if (!core->fwk_version_supported)
			return -ENOTSUPP;
		else
			return 0;
	}


	return rc;
}