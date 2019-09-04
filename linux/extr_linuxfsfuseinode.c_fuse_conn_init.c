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
struct user_namespace {int dummy; } ;
struct fuse_conn {int connected; int attr_version; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  pid_ns; int /*<<< orphan*/  scramble_key; scalar_t__ initialized; scalar_t__ blocked; int /*<<< orphan*/  polled_files; scalar_t__ khctr; int /*<<< orphan*/  congestion_threshold; int /*<<< orphan*/  max_background; int /*<<< orphan*/  num_waiting; int /*<<< orphan*/  devices; int /*<<< orphan*/  entry; int /*<<< orphan*/  bg_queue; int /*<<< orphan*/  iq; int /*<<< orphan*/  reserved_req_waitq; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  dev_count; int /*<<< orphan*/  count; int /*<<< orphan*/  killsb; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DEFAULT_CONGESTION_THRESHOLD ; 
 int /*<<< orphan*/  FUSE_DEFAULT_MAX_BACKGROUND ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fuse_iqueue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fuse_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 

void fuse_conn_init(struct fuse_conn *fc, struct user_namespace *user_ns)
{
	memset(fc, 0, sizeof(*fc));
	spin_lock_init(&fc->lock);
	init_rwsem(&fc->killsb);
	refcount_set(&fc->count, 1);
	atomic_set(&fc->dev_count, 1);
	init_waitqueue_head(&fc->blocked_waitq);
	init_waitqueue_head(&fc->reserved_req_waitq);
	fuse_iqueue_init(&fc->iq);
	INIT_LIST_HEAD(&fc->bg_queue);
	INIT_LIST_HEAD(&fc->entry);
	INIT_LIST_HEAD(&fc->devices);
	atomic_set(&fc->num_waiting, 0);
	fc->max_background = FUSE_DEFAULT_MAX_BACKGROUND;
	fc->congestion_threshold = FUSE_DEFAULT_CONGESTION_THRESHOLD;
	fc->khctr = 0;
	fc->polled_files = RB_ROOT;
	fc->blocked = 0;
	fc->initialized = 0;
	fc->connected = 1;
	fc->attr_version = 1;
	get_random_bytes(&fc->scramble_key, sizeof(fc->scramble_key));
	fc->pid_ns = get_pid_ns(task_active_pid_ns(current));
	fc->user_ns = get_user_ns(user_ns);
}