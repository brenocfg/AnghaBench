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
struct task_struct {int /*<<< orphan*/ * kcov; int /*<<< orphan*/ * kcov_area; scalar_t__ kcov_size; int /*<<< orphan*/  kcov_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCOV_MODE_DISABLED ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 

void kcov_task_init(struct task_struct *t)
{
	WRITE_ONCE(t->kcov_mode, KCOV_MODE_DISABLED);
	barrier();
	t->kcov_size = 0;
	t->kcov_area = NULL;
	t->kcov = NULL;
}