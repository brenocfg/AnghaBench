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
struct l2cap_conn {TYPE_1__* hcon; } ;
struct l2cap_chan {struct amp_mgr* data; } ;
struct amp_mgr {int /*<<< orphan*/  list; int /*<<< orphan*/  amp_ctrls_lock; int /*<<< orphan*/  amp_ctrls; int /*<<< orphan*/  kref; struct l2cap_chan* a2mp_chan; struct l2cap_conn* l2cap_conn; } ;
struct TYPE_2__ {struct amp_mgr* amp_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*,struct amp_mgr*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct l2cap_chan* a2mp_chan_open (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  amp_mgr_list ; 
 int /*<<< orphan*/  amp_mgr_list_lock ; 
 int /*<<< orphan*/  kfree (struct amp_mgr*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct amp_mgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct amp_mgr *amp_mgr_create(struct l2cap_conn *conn, bool locked)
{
	struct amp_mgr *mgr;
	struct l2cap_chan *chan;

	mgr = kzalloc(sizeof(*mgr), GFP_KERNEL);
	if (!mgr)
		return NULL;

	BT_DBG("conn %p mgr %p", conn, mgr);

	mgr->l2cap_conn = conn;

	chan = a2mp_chan_open(conn, locked);
	if (!chan) {
		kfree(mgr);
		return NULL;
	}

	mgr->a2mp_chan = chan;
	chan->data = mgr;

	conn->hcon->amp_mgr = mgr;

	kref_init(&mgr->kref);

	/* Remote AMP ctrl list initialization */
	INIT_LIST_HEAD(&mgr->amp_ctrls);
	mutex_init(&mgr->amp_ctrls_lock);

	mutex_lock(&amp_mgr_list_lock);
	list_add(&mgr->list, &amp_mgr_list);
	mutex_unlock(&amp_mgr_list_lock);

	return mgr;
}