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
struct tcp_congestion_ops {scalar_t__ key; int /*<<< orphan*/  name; int /*<<< orphan*/  list; scalar_t__ cong_control; scalar_t__ cong_avoid; int /*<<< orphan*/  undo_cwnd; int /*<<< orphan*/  ssthresh; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ TCP_CA_UNSPEC ; 
 scalar_t__ jhash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_ca_find_key (scalar_t__) ; 
 int /*<<< orphan*/  tcp_cong_list ; 
 int /*<<< orphan*/  tcp_cong_list_lock ; 

int tcp_register_congestion_control(struct tcp_congestion_ops *ca)
{
	int ret = 0;

	/* all algorithms must implement these */
	if (!ca->ssthresh || !ca->undo_cwnd ||
	    !(ca->cong_avoid || ca->cong_control)) {
		pr_err("%s does not implement required ops\n", ca->name);
		return -EINVAL;
	}

	ca->key = jhash(ca->name, sizeof(ca->name), strlen(ca->name));

	spin_lock(&tcp_cong_list_lock);
	if (ca->key == TCP_CA_UNSPEC || tcp_ca_find_key(ca->key)) {
		pr_notice("%s already registered or non-unique key\n",
			  ca->name);
		ret = -EEXIST;
	} else {
		list_add_tail_rcu(&ca->list, &tcp_cong_list);
		pr_debug("%s registered\n", ca->name);
	}
	spin_unlock(&tcp_cong_list_lock);

	return ret;
}