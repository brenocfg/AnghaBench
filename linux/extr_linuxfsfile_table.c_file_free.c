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
struct TYPE_2__ {int /*<<< orphan*/  fu_rcuhead; } ;
struct file {int f_mode; TYPE_1__ f_u; } ;

/* Variables and functions */
 int FMODE_NOACCOUNT ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_free_rcu ; 
 int /*<<< orphan*/  nr_files ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_file_free (struct file*) ; 

__attribute__((used)) static inline void file_free(struct file *f)
{
	security_file_free(f);
	if (!(f->f_mode & FMODE_NOACCOUNT))
		percpu_counter_dec(&nr_files);
	call_rcu(&f->f_u.fu_rcuhead, file_free_rcu);
}