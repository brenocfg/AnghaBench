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
typedef  int /*<<< orphan*/  u16 ;
struct wsm_mib {void* buf; size_t buf_size; int /*<<< orphan*/  mib_id; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_READ_MIB_REQ_ID ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,struct wsm_mib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_read_mib(struct cw1200_common *priv, u16 mib_id, void *_buf,
			size_t buf_size)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;
	struct wsm_mib mib_buf = {
		.mib_id = mib_id,
		.buf = _buf,
		.buf_size = buf_size,
	};
	wsm_cmd_lock(priv);

	WSM_PUT16(buf, mib_id);
	WSM_PUT16(buf, 0);

	ret = wsm_cmd_send(priv, buf, &mib_buf,
			   WSM_READ_MIB_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}