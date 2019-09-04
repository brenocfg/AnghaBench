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
struct cpuacct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuacct_cgrp_id ; 
 struct cpuacct* css_ca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_css (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cpuacct *task_ca(struct task_struct *tsk)
{
	return css_ca(task_css(tsk, cpuacct_cgrp_id));
}