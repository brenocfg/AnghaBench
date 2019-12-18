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
struct file {int dummy; } ;
struct ecryptfs_daemon {int /*<<< orphan*/  euid_chain; scalar_t__ num_queued_msg_ctx; int /*<<< orphan*/  wait; int /*<<< orphan*/  msg_ctx_out_queue; int /*<<< orphan*/  mux; struct file* file; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t ecryptfs_current_euid_hash () ; 
 int /*<<< orphan*/ * ecryptfs_daemon_hash ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ecryptfs_daemon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int
ecryptfs_spawn_daemon(struct ecryptfs_daemon **daemon, struct file *file)
{
	int rc = 0;

	(*daemon) = kzalloc(sizeof(**daemon), GFP_KERNEL);
	if (!(*daemon)) {
		rc = -ENOMEM;
		goto out;
	}
	(*daemon)->file = file;
	mutex_init(&(*daemon)->mux);
	INIT_LIST_HEAD(&(*daemon)->msg_ctx_out_queue);
	init_waitqueue_head(&(*daemon)->wait);
	(*daemon)->num_queued_msg_ctx = 0;
	hlist_add_head(&(*daemon)->euid_chain,
		       &ecryptfs_daemon_hash[ecryptfs_current_euid_hash()]);
out:
	return rc;
}