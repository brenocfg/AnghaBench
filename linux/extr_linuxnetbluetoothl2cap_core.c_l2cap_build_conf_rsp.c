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
struct l2cap_conf_rsp {void* flags; void* result; void* scid; void* data; } ;
struct l2cap_chan {int /*<<< orphan*/  dcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_build_conf_rsp(struct l2cap_chan *chan, void *data,
				u16 result, u16 flags)
{
	struct l2cap_conf_rsp *rsp = data;
	void *ptr = rsp->data;

	BT_DBG("chan %p", chan);

	rsp->scid   = cpu_to_le16(chan->dcid);
	rsp->result = cpu_to_le16(result);
	rsp->flags  = cpu_to_le16(flags);

	return ptr - data;
}