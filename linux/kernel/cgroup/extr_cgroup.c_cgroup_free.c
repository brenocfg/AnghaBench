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
struct css_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_css_set (struct css_set*) ; 
 struct css_set* task_css_set (struct task_struct*) ; 

void cgroup_free(struct task_struct *task)
{
	struct css_set *cset = task_css_set(task);
	put_css_set(cset);
}