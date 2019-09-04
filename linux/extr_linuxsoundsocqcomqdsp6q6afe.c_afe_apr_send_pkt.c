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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct TYPE_2__ {scalar_t__ opcode; int status; } ;
struct q6afe_port {TYPE_1__ result; int /*<<< orphan*/  wait; } ;
struct q6afe {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  apr; } ;
struct apr_hdr {scalar_t__ opcode; } ;
struct apr_pkt {struct apr_hdr hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afe_apr_send_pkt(struct q6afe *afe, struct apr_pkt *pkt,
			    struct q6afe_port *port)
{
	wait_queue_head_t *wait = &port->wait;
	struct apr_hdr *hdr = &pkt->hdr;
	int ret;

	mutex_lock(&afe->lock);
	port->result.opcode = 0;
	port->result.status = 0;

	ret = apr_send_pkt(afe->apr, pkt);
	if (ret < 0) {
		dev_err(afe->dev, "packet not transmitted (%d)\n", ret);
		ret = -EINVAL;
		goto err;
	}

	ret = wait_event_timeout(*wait, (port->result.opcode == hdr->opcode),
				 msecs_to_jiffies(TIMEOUT_MS));
	if (!ret) {
		ret = -ETIMEDOUT;
	} else if (port->result.status > 0) {
		dev_err(afe->dev, "DSP returned error[%x]\n",
			port->result.status);
		ret = -EINVAL;
	} else {
		ret = 0;
	}

err:
	mutex_unlock(&afe->lock);

	return ret;
}