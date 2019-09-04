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
struct wsm_buf {int dummy; } ;
struct wsm_beacon_transmit {scalar_t__ enable_beaconing; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_BEACON_TRANSMIT_REQ_ID ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_beacon_transmit(struct cw1200_common *priv,
			const struct wsm_beacon_transmit *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->enable_beaconing ? 1 : 0);

	ret = wsm_cmd_send(priv, buf, NULL,
			   WSM_BEACON_TRANSMIT_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}