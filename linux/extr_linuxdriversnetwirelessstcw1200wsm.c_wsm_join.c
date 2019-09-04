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
struct wsm_join_cnf {int /*<<< orphan*/  status; } ;
struct wsm_join {int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/ * ssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  probe_for_join; int /*<<< orphan*/  preamble_type; int /*<<< orphan*/  atim_window; int /*<<< orphan*/ * bssid; int /*<<< orphan*/  channel_number; int /*<<< orphan*/  band; int /*<<< orphan*/  mode; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int tx_burst_idx; int /*<<< orphan*/  join_complete_status; struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_JOIN_REQ_ID ; 
 int /*<<< orphan*/  WSM_PUT (struct wsm_buf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT8 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,struct wsm_join_cnf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_join(struct cw1200_common *priv, struct wsm_join *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;
	struct wsm_join_cnf resp;
	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->band);
	WSM_PUT16(buf, arg->channel_number);
	WSM_PUT(buf, &arg->bssid[0], sizeof(arg->bssid));
	WSM_PUT16(buf, arg->atim_window);
	WSM_PUT8(buf, arg->preamble_type);
	WSM_PUT8(buf, arg->probe_for_join);
	WSM_PUT8(buf, arg->dtim_period);
	WSM_PUT8(buf, arg->flags);
	WSM_PUT32(buf, arg->ssid_len);
	WSM_PUT(buf, &arg->ssid[0], sizeof(arg->ssid));
	WSM_PUT32(buf, arg->beacon_interval);
	WSM_PUT32(buf, arg->basic_rate_set);

	priv->tx_burst_idx = -1;
	ret = wsm_cmd_send(priv, buf, &resp,
			   WSM_JOIN_REQ_ID, WSM_CMD_TIMEOUT);
	/* TODO:  Update state based on resp.min|max_power_level */

	priv->join_complete_status = resp.status;

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}