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
struct pid {int dummy; } ;
struct file {int dummy; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int /*<<< orphan*/  f_modown (struct file*,struct pid*,int,int) ; 
 int /*<<< orphan*/  security_file_set_fowner (struct file*) ; 

void __f_setown(struct file *filp, struct pid *pid, enum pid_type type,
		int force)
{
	security_file_set_fowner(filp);
	f_modown(filp, pid, type, force);
}