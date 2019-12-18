#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ opcode; int /*<<< orphan*/  status; } ;
struct q6copp {TYPE_2__ result; int /*<<< orphan*/  wait; } ;
struct q6adm {int /*<<< orphan*/  lock; int /*<<< orphan*/  apr; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ opcode; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6adm_apr_send_copp_pkt(struct q6adm *adm, struct q6copp *copp,
				   struct apr_pkt *pkt, uint32_t rsp_opcode)
{
	struct device *dev = adm->dev;
	uint32_t opcode = pkt->hdr.opcode;
	int ret;

	mutex_lock(&adm->lock);
	copp->result.opcode = 0;
	copp->result.status = 0;
	ret = apr_send_pkt(adm->apr, pkt);
	if (ret < 0) {
		dev_err(dev, "Failed to send APR packet\n");
		ret = -EINVAL;
		goto err;
	}

	/* Wait for the callback with copp id */
	if (rsp_opcode)
		ret = wait_event_timeout(copp->wait,
					 (copp->result.opcode == opcode) ||
					 (copp->result.opcode == rsp_opcode),
					 msecs_to_jiffies(TIMEOUT_MS));
	else
		ret = wait_event_timeout(copp->wait,
					 (copp->result.opcode == opcode),
					 msecs_to_jiffies(TIMEOUT_MS));

	if (!ret) {
		dev_err(dev, "ADM copp cmd timedout\n");
		ret = -ETIMEDOUT;
	} else if (copp->result.status > 0) {
		dev_err(dev, "DSP returned error[%d]\n",
			copp->result.status);
		ret = -EINVAL;
	}

err:
	mutex_unlock(&adm->lock);
	return ret;
}