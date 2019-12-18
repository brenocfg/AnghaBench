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
struct freezer {int dummy; } ;

/* Variables and functions */
 struct freezer* css_freezer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freezer_cgrp_id ; 
 int /*<<< orphan*/  task_css (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct freezer *task_freezer(struct task_struct *task)
{
	return css_freezer(task_css(task, freezer_cgrp_id));
}