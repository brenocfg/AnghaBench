#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int eof; scalar_t__ w_pos; } ;
struct tomoyo_io_buffer {char* write_buf; TYPE_1__ r; } ;
struct tomoyo_domain_info {TYPE_2__* domainname; int /*<<< orphan*/  profile; } ;
struct task_struct {int dummy; } ;
struct TYPE_6__ {struct tomoyo_domain_info* domain_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct task_struct* find_task_by_pid_ns (unsigned int,int /*<<< orphan*/ *) ; 
 struct task_struct* find_task_by_vpid (unsigned int) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 scalar_t__ kstrtouint (char*,int,unsigned int*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_set_string (struct tomoyo_io_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ tomoyo_str_starts (char**,char*) ; 
 TYPE_3__* tomoyo_task (struct task_struct*) ; 

__attribute__((used)) static void tomoyo_read_pid(struct tomoyo_io_buffer *head)
{
	char *buf = head->write_buf;
	bool global_pid = false;
	unsigned int pid;
	struct task_struct *p;
	struct tomoyo_domain_info *domain = NULL;

	/* Accessing write_buf is safe because head->io_sem is held. */
	if (!buf) {
		head->r.eof = true;
		return; /* Do nothing if open(O_RDONLY). */
	}
	if (head->r.w_pos || head->r.eof)
		return;
	head->r.eof = true;
	if (tomoyo_str_starts(&buf, "global-pid "))
		global_pid = true;
	if (kstrtouint(buf, 10, &pid))
		return;
	rcu_read_lock();
	if (global_pid)
		p = find_task_by_pid_ns(pid, &init_pid_ns);
	else
		p = find_task_by_vpid(pid);
	if (p)
		domain = tomoyo_task(p)->domain_info;
	rcu_read_unlock();
	if (!domain)
		return;
	tomoyo_io_printf(head, "%u %u ", pid, domain->profile);
	tomoyo_set_string(head, domain->domainname->name);
}