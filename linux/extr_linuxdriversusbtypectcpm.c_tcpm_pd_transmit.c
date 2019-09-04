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
struct tcpm_port {int tx_status; int message_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_complete; TYPE_1__* tcpc; } ;
struct pd_message {int /*<<< orphan*/  header; } ;
typedef  enum tcpm_transmit_type { ____Placeholder_tcpm_transmit_type } tcpm_transmit_type ;
struct TYPE_2__ {int (* pd_transmit ) (TYPE_1__*,int,struct pd_message const*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int PD_HEADER_ID_MASK ; 
 int /*<<< orphan*/  PD_T_TCPC_TX_TIMEOUT ; 
#define  TCPC_TX_DISCARDED 130 
#define  TCPC_TX_FAILED 129 
#define  TCPC_TX_SUCCESS 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int,struct pd_message const*) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_pd_transmit(struct tcpm_port *port,
			    enum tcpm_transmit_type type,
			    const struct pd_message *msg)
{
	unsigned long timeout;
	int ret;

	if (msg)
		tcpm_log(port, "PD TX, header: %#x", le16_to_cpu(msg->header));
	else
		tcpm_log(port, "PD TX, type: %#x", type);

	reinit_completion(&port->tx_complete);
	ret = port->tcpc->pd_transmit(port->tcpc, type, msg);
	if (ret < 0)
		return ret;

	mutex_unlock(&port->lock);
	timeout = wait_for_completion_timeout(&port->tx_complete,
				msecs_to_jiffies(PD_T_TCPC_TX_TIMEOUT));
	mutex_lock(&port->lock);
	if (!timeout)
		return -ETIMEDOUT;

	switch (port->tx_status) {
	case TCPC_TX_SUCCESS:
		port->message_id = (port->message_id + 1) & PD_HEADER_ID_MASK;
		return 0;
	case TCPC_TX_DISCARDED:
		return -EAGAIN;
	case TCPC_TX_FAILED:
	default:
		return -EIO;
	}
}