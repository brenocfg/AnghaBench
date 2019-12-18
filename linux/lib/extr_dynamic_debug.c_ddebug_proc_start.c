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
struct seq_file {struct ddebug_iter* private; } ;
struct ddebug_iter {int dummy; } ;
typedef  void _ddebug ;
typedef  int loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 void* ddebug_iter_first (struct ddebug_iter*) ; 
 void* ddebug_iter_next (struct ddebug_iter*) ; 
 int /*<<< orphan*/  ddebug_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpr_info (char*,struct seq_file*,unsigned long long) ; 

__attribute__((used)) static void *ddebug_proc_start(struct seq_file *m, loff_t *pos)
{
	struct ddebug_iter *iter = m->private;
	struct _ddebug *dp;
	int n = *pos;

	vpr_info("called m=%p *pos=%lld\n", m, (unsigned long long)*pos);

	mutex_lock(&ddebug_lock);

	if (!n)
		return SEQ_START_TOKEN;
	if (n < 0)
		return NULL;
	dp = ddebug_iter_first(iter);
	while (dp != NULL && --n > 0)
		dp = ddebug_iter_next(iter);
	return dp;
}