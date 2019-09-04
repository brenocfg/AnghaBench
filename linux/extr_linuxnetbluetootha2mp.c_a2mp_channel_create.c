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
struct sk_buff {int dummy; } ;
struct l2cap_conn {TYPE_1__* hcon; } ;
struct l2cap_chan {int dummy; } ;
struct amp_mgr {struct l2cap_chan* a2mp_chan; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct amp_mgr*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 struct amp_mgr* amp_mgr_create (struct l2cap_conn*,int) ; 

struct l2cap_chan *a2mp_channel_create(struct l2cap_conn *conn,
				       struct sk_buff *skb)
{
	struct amp_mgr *mgr;

	if (conn->hcon->type != ACL_LINK)
		return NULL;

	mgr = amp_mgr_create(conn, false);
	if (!mgr) {
		BT_ERR("Could not create AMP manager");
		return NULL;
	}

	BT_DBG("mgr: %p chan %p", mgr, mgr->a2mp_chan);

	return mgr->a2mp_chan;
}