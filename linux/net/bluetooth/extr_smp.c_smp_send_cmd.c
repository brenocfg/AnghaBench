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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct smp_chan {int /*<<< orphan*/  security_timer; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct l2cap_conn {struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_TIMEOUT ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 int /*<<< orphan*/  l2cap_chan_send (struct l2cap_chan*,struct msghdr*,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smp_send_cmd(struct l2cap_conn *conn, u8 code, u16 len, void *data)
{
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp;
	struct kvec iv[2];
	struct msghdr msg;

	if (!chan)
		return;

	BT_DBG("code 0x%2.2x", code);

	iv[0].iov_base = &code;
	iv[0].iov_len = 1;

	iv[1].iov_base = data;
	iv[1].iov_len = len;

	memset(&msg, 0, sizeof(msg));

	iov_iter_kvec(&msg.msg_iter, WRITE, iv, 2, 1 + len);

	l2cap_chan_send(chan, &msg, 1 + len);

	if (!chan->data)
		return;

	smp = chan->data;

	cancel_delayed_work_sync(&smp->security_timer);
	schedule_delayed_work(&smp->security_timer, SMP_TIMEOUT);
}