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
struct task_struct {struct task_struct* group_leader; } ;

/* Variables and functions */
 int KDB_ARGCOUNT ; 
 int KDB_BADINT ; 
 struct task_struct* find_task_by_pid_ns (long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  kdb_printf (char*) ; 
 int /*<<< orphan*/  kdb_send_sig (struct task_struct*,long) ; 
 long simple_strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_signal (long) ; 

__attribute__((used)) static int kdb_kill(int argc, const char **argv)
{
	long sig, pid;
	char *endp;
	struct task_struct *p;

	if (argc != 2)
		return KDB_ARGCOUNT;

	sig = simple_strtol(argv[1], &endp, 0);
	if (*endp)
		return KDB_BADINT;
	if ((sig >= 0) || !valid_signal(-sig)) {
		kdb_printf("Invalid signal parameter.<-signal>\n");
		return 0;
	}
	sig = -sig;

	pid = simple_strtol(argv[2], &endp, 0);
	if (*endp)
		return KDB_BADINT;
	if (pid <= 0) {
		kdb_printf("Process ID must be large than 0.\n");
		return 0;
	}

	/* Find the process. */
	p = find_task_by_pid_ns(pid, &init_pid_ns);
	if (!p) {
		kdb_printf("The specified process isn't found.\n");
		return 0;
	}
	p = p->group_leader;
	kdb_send_sig(p, sig);
	return 0;
}