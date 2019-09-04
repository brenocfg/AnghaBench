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
struct tracer_stat {scalar_t__ stat_cmp; void* (* stat_next ) (void*,int) ;void* (* stat_start ) (struct tracer_stat*) ;} ;
struct rb_root {int dummy; } ;
struct stat_session {int /*<<< orphan*/  stat_mutex; struct rb_root stat_root; struct tracer_stat* ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_stat_session (struct stat_session*) ; 
 scalar_t__ dummy_cmp ; 
 int insert_stat (struct rb_root*,void*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* stub1 (struct tracer_stat*) ; 
 void* stub2 (void*,int) ; 

__attribute__((used)) static int stat_seq_init(struct stat_session *session)
{
	struct tracer_stat *ts = session->ts;
	struct rb_root *root = &session->stat_root;
	void *stat;
	int ret = 0;
	int i;

	mutex_lock(&session->stat_mutex);
	__reset_stat_session(session);

	if (!ts->stat_cmp)
		ts->stat_cmp = dummy_cmp;

	stat = ts->stat_start(ts);
	if (!stat)
		goto exit;

	ret = insert_stat(root, stat, ts->stat_cmp);
	if (ret)
		goto exit;

	/*
	 * Iterate over the tracer stat entries and store them in an rbtree.
	 */
	for (i = 1; ; i++) {
		stat = ts->stat_next(stat, i);

		/* End of insertion */
		if (!stat)
			break;

		ret = insert_stat(root, stat, ts->stat_cmp);
		if (ret)
			goto exit_free_rbtree;
	}

exit:
	mutex_unlock(&session->stat_mutex);
	return ret;

exit_free_rbtree:
	__reset_stat_session(session);
	mutex_unlock(&session->stat_mutex);
	return ret;
}