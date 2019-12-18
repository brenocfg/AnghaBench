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
struct task_struct {char* comm; } ;
struct seq_file {int dummy; } ;
struct gfs2_holder {scalar_t__ gh_ip; scalar_t__ gh_owner_pid; int /*<<< orphan*/  gh_error; int /*<<< orphan*/  gh_iflags; int /*<<< orphan*/  gh_flags; int /*<<< orphan*/  gh_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  gfs2_print_dbg (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,char*,void*) ; 
 int /*<<< orphan*/  hflags2str (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pid_nr (scalar_t__) ; 
 struct task_struct* pid_task (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  state2str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_holder(struct seq_file *seq, const struct gfs2_holder *gh,
			const char *fs_id_buf)
{
	struct task_struct *gh_owner = NULL;
	char flags_buf[32];

	rcu_read_lock();
	if (gh->gh_owner_pid)
		gh_owner = pid_task(gh->gh_owner_pid, PIDTYPE_PID);
	gfs2_print_dbg(seq, "%s H: s:%s f:%s e:%d p:%ld [%s] %pS\n",
		       fs_id_buf, state2str(gh->gh_state),
		       hflags2str(flags_buf, gh->gh_flags, gh->gh_iflags),
		       gh->gh_error,
		       gh->gh_owner_pid ? (long)pid_nr(gh->gh_owner_pid) : -1,
		       gh_owner ? gh_owner->comm : "(ended)",
		       (void *)gh->gh_ip);
	rcu_read_unlock();
}