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
struct wsm_start {int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  probe_delay; int /*<<< orphan*/  preamble; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  ct_window; int /*<<< orphan*/  channel_number; int /*<<< orphan*/  band; int /*<<< orphan*/  mode; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int tx_burst_idx; struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_START_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT (struct wsm_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT8 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_START_REQ_ID ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_start(struct cw1200_common *priv, const struct wsm_start *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->band);
	WSM_PUT16(buf, arg->channel_number);
	WSM_PUT32(buf, arg->ct_window);
	WSM_PUT32(buf, arg->beacon_interval);
	WSM_PUT8(buf, arg->dtim_period);
	WSM_PUT8(buf, arg->preamble);
	WSM_PUT8(buf, arg->probe_delay);
	WSM_PUT8(buf, arg->ssid_len);
	WSM_PUT(buf, arg->ssid, sizeof(arg->ssid));
	WSM_PUT32(buf, arg->basic_rate_set);

	priv->tx_burst_idx = -1;
	ret = wsm_cmd_send(priv, buf, NULL,
			   WSM_START_REQ_ID, WSM_CMD_START_TIMEOUT);

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}