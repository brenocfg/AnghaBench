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
struct taskstats {int dummy; } ;
struct task_struct {TYPE_1__* signal; } ;
struct sk_buff {int dummy; } ;
struct listener_list {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASKSTATS_CMD_NEW ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_PID ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_TGID ; 
 int /*<<< orphan*/  family_registered ; 
 int /*<<< orphan*/  fill_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct task_struct*,struct taskstats*) ; 
 int /*<<< orphan*/  fill_tgid_exit (struct task_struct*) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listener_array ; 
 int /*<<< orphan*/  memcpy (struct taskstats*,int /*<<< orphan*/ ,int) ; 
 struct taskstats* mk_reply (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int prepare_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff**,size_t) ; 
 struct listener_list* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_cpu_listeners (struct sk_buff*,struct listener_list*) ; 
 int /*<<< orphan*/  task_pid_nr_ns (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_tgid_nr_ns (struct task_struct*,int /*<<< orphan*/ *) ; 
 size_t taskstats_packet_size () ; 
 int /*<<< orphan*/  taskstats_tgid_alloc (struct task_struct*) ; 

void taskstats_exit(struct task_struct *tsk, int group_dead)
{
	int rc;
	struct listener_list *listeners;
	struct taskstats *stats;
	struct sk_buff *rep_skb;
	size_t size;
	int is_thread_group;

	if (!family_registered)
		return;

	/*
	 * Size includes space for nested attributes
	 */
	size = taskstats_packet_size();

	is_thread_group = !!taskstats_tgid_alloc(tsk);
	if (is_thread_group) {
		/* PID + STATS + TGID + STATS */
		size = 2 * size;
		/* fill the tsk->signal->stats structure */
		fill_tgid_exit(tsk);
	}

	listeners = raw_cpu_ptr(&listener_array);
	if (list_empty(&listeners->list))
		return;

	rc = prepare_reply(NULL, TASKSTATS_CMD_NEW, &rep_skb, size);
	if (rc < 0)
		return;

	stats = mk_reply(rep_skb, TASKSTATS_TYPE_PID,
			 task_pid_nr_ns(tsk, &init_pid_ns));
	if (!stats)
		goto err;

	fill_stats(&init_user_ns, &init_pid_ns, tsk, stats);

	/*
	 * Doesn't matter if tsk is the leader or the last group member leaving
	 */
	if (!is_thread_group || !group_dead)
		goto send;

	stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID,
			 task_tgid_nr_ns(tsk, &init_pid_ns));
	if (!stats)
		goto err;

	memcpy(stats, tsk->signal->stats, sizeof(*stats));

send:
	send_cpu_listeners(rep_skb, listeners);
	return;
err:
	nlmsg_free(rep_skb);
}