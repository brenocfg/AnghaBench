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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct iucv_tty_buffer {int /*<<< orphan*/  list; TYPE_2__ msg; TYPE_1__* mbuf; } ;
struct hvc_iucv_private {scalar_t__ iucv_state; int sndbuf_len; int /*<<< orphan*/  path; int /*<<< orphan*/  tty_outqueue; int /*<<< orphan*/  sndbuf; } ;
struct TYPE_3__ {scalar_t__ datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IUCV_DISCONN ; 
 scalar_t__ IUCV_SEVERED ; 
 int /*<<< orphan*/  MSG_SIZE (scalar_t__) ; 
 int __iucv_message_send (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct iucv_tty_buffer* alloc_tty_buffer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_tty_buffer (struct iucv_tty_buffer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hvc_iucv_send(struct hvc_iucv_private *priv)
{
	struct iucv_tty_buffer *sb;
	int rc, len;

	if (priv->iucv_state == IUCV_SEVERED)
		return -EPIPE;

	if (priv->iucv_state == IUCV_DISCONN)
		return -EIO;

	if (!priv->sndbuf_len)
		return 0;

	/* allocate internal buffer to store msg data and also compute total
	 * message length */
	sb = alloc_tty_buffer(priv->sndbuf_len, GFP_ATOMIC);
	if (!sb)
		return -ENOMEM;

	memcpy(sb->mbuf->data, priv->sndbuf, priv->sndbuf_len);
	sb->mbuf->datalen = (u16) priv->sndbuf_len;
	sb->msg.length = MSG_SIZE(sb->mbuf->datalen);

	list_add_tail(&sb->list, &priv->tty_outqueue);

	rc = __iucv_message_send(priv->path, &sb->msg, 0, 0,
				 (void *) sb->mbuf, sb->msg.length);
	if (rc) {
		/* drop the message here; however we might want to handle
		 * 0x03 (msg limit reached) by trying again... */
		list_del(&sb->list);
		destroy_tty_buffer(sb);
	}
	len = priv->sndbuf_len;
	priv->sndbuf_len = 0;

	return len;
}