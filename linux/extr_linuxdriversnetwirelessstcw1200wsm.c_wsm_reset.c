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
typedef  int u16 ;
struct wsm_reset {scalar_t__ reset_statistics; int /*<<< orphan*/  link_id; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_RESET_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int) ; 
 int WSM_RESET_REQ_ID ; 
 int WSM_TX_LINK_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_reset(struct cw1200_common *priv, const struct wsm_reset *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;
	u16 cmd = WSM_RESET_REQ_ID | WSM_TX_LINK_ID(arg->link_id);

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->reset_statistics ? 0 : 1);
	ret = wsm_cmd_send(priv, buf, NULL, cmd, WSM_CMD_RESET_TIMEOUT);
	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}