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
typedef  scalar_t__ u16 ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct l2cap_chan {int dummy; } ;
struct kvec {scalar_t__ iov_len; struct a2mp_cmd* iov_base; } ;
struct amp_mgr {struct l2cap_chan* a2mp_chan; } ;
struct a2mp_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 struct a2mp_cmd* __a2mp_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct a2mp_cmd*) ; 
 int /*<<< orphan*/  l2cap_chan_send (struct l2cap_chan*,struct msghdr*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a2mp_send(struct amp_mgr *mgr, u8 code, u8 ident, u16 len, void *data)
{
	struct l2cap_chan *chan = mgr->a2mp_chan;
	struct a2mp_cmd *cmd;
	u16 total_len = len + sizeof(*cmd);
	struct kvec iv;
	struct msghdr msg;

	cmd = __a2mp_build(code, ident, len, data);
	if (!cmd)
		return;

	iv.iov_base = cmd;
	iv.iov_len = total_len;

	memset(&msg, 0, sizeof(msg));

	iov_iter_kvec(&msg.msg_iter, WRITE, &iv, 1, total_len);

	l2cap_chan_send(chan, &msg, total_len);

	kfree(cmd);
}