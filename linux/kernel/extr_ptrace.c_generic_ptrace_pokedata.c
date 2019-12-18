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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int EIO ; 
 int FOLL_FORCE ; 
 int FOLL_WRITE ; 
 int ptrace_access_vm (struct task_struct*,unsigned long,unsigned long*,int,int) ; 

int generic_ptrace_pokedata(struct task_struct *tsk, unsigned long addr,
			    unsigned long data)
{
	int copied;

	copied = ptrace_access_vm(tsk, addr, &data, sizeof(data),
			FOLL_FORCE | FOLL_WRITE);
	return (copied == sizeof(data)) ? 0 : -EIO;
}