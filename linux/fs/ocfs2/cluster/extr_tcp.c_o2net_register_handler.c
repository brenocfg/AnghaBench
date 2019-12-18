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
typedef  scalar_t__ u32 ;
struct rb_node {int dummy; } ;
struct o2net_msg_handler {int /*<<< orphan*/  nh_unregister_item; int /*<<< orphan*/  nh_node; int /*<<< orphan*/  nh_kref; scalar_t__ nh_key; scalar_t__ nh_max_len; scalar_t__ nh_msg_type; int /*<<< orphan*/ * nh_post_func; void* nh_func_data; int /*<<< orphan*/ * nh_func; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  o2net_post_msg_handler_func ;
typedef  int /*<<< orphan*/  o2net_msg_handler_func ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_TCP ; 
 scalar_t__ O2NET_MAX_PAYLOAD_BYTES ; 
 int /*<<< orphan*/  kfree (struct o2net_msg_handler*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct o2net_msg_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  o2net_handler_lock ; 
 int /*<<< orphan*/  o2net_handler_tree ; 
 int /*<<< orphan*/ * o2net_handler_tree_lookup (scalar_t__,scalar_t__,struct rb_node***,struct rb_node**) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int o2net_register_handler(u32 msg_type, u32 key, u32 max_len,
			   o2net_msg_handler_func *func, void *data,
			   o2net_post_msg_handler_func *post_func,
			   struct list_head *unreg_list)
{
	struct o2net_msg_handler *nmh = NULL;
	struct rb_node **p, *parent;
	int ret = 0;

	if (max_len > O2NET_MAX_PAYLOAD_BYTES) {
		mlog(0, "max_len for message handler out of range: %u\n",
			max_len);
		ret = -EINVAL;
		goto out;
	}

	if (!msg_type) {
		mlog(0, "no message type provided: %u, %p\n", msg_type, func);
		ret = -EINVAL;
		goto out;

	}
	if (!func) {
		mlog(0, "no message handler provided: %u, %p\n",
		       msg_type, func);
		ret = -EINVAL;
		goto out;
	}

       	nmh = kzalloc(sizeof(struct o2net_msg_handler), GFP_NOFS);
	if (nmh == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	nmh->nh_func = func;
	nmh->nh_func_data = data;
	nmh->nh_post_func = post_func;
	nmh->nh_msg_type = msg_type;
	nmh->nh_max_len = max_len;
	nmh->nh_key = key;
	/* the tree and list get this ref.. they're both removed in
	 * unregister when this ref is dropped */
	kref_init(&nmh->nh_kref);
	INIT_LIST_HEAD(&nmh->nh_unregister_item);

	write_lock(&o2net_handler_lock);
	if (o2net_handler_tree_lookup(msg_type, key, &p, &parent))
		ret = -EEXIST;
	else {
	        rb_link_node(&nmh->nh_node, parent, p);
		rb_insert_color(&nmh->nh_node, &o2net_handler_tree);
		list_add_tail(&nmh->nh_unregister_item, unreg_list);

		mlog(ML_TCP, "registered handler func %p type %u key %08x\n",
		     func, msg_type, key);
		/* we've had some trouble with handlers seemingly vanishing. */
		mlog_bug_on_msg(o2net_handler_tree_lookup(msg_type, key, &p,
							  &parent) == NULL,
			        "couldn't find handler we *just* registered "
				"for type %u key %08x\n", msg_type, key);
	}
	write_unlock(&o2net_handler_lock);

out:
	if (ret)
		kfree(nmh);

	return ret;
}