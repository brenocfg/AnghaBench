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
struct TYPE_2__ {scalar_t__ opcode; scalar_t__ status; } ;
struct audio_client {int /*<<< orphan*/  cmd_lock; TYPE_1__ result; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  adev; } ;
struct apr_hdr {scalar_t__ opcode; } ;
struct apr_pkt {struct apr_hdr hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int q6asm_ac_send_cmd_sync(struct audio_client *ac, struct apr_pkt *pkt)
{
	struct apr_hdr *hdr = &pkt->hdr;
	int rc;

	mutex_lock(&ac->cmd_lock);
	ac->result.opcode = 0;
	ac->result.status = 0;

	rc = apr_send_pkt(ac->adev, pkt);
	if (rc < 0)
		goto err;

	rc = wait_event_timeout(ac->cmd_wait,
				(ac->result.opcode == hdr->opcode), 5 * HZ);
	if (!rc) {
		dev_err(ac->dev, "CMD timeout\n");
		rc =  -ETIMEDOUT;
		goto err;
	}

	if (ac->result.status > 0) {
		dev_err(ac->dev, "DSP returned error[%x]\n",
			ac->result.status);
		rc = -EINVAL;
	} else {
		rc = 0;
	}


err:
	mutex_unlock(&ac->cmd_lock);
	return rc;
}