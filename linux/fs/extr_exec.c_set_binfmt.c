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
struct mm_struct {struct linux_binfmt* binfmt; } ;
struct linux_binfmt {int /*<<< orphan*/  module; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void set_binfmt(struct linux_binfmt *new)
{
	struct mm_struct *mm = current->mm;

	if (mm->binfmt)
		module_put(mm->binfmt->module);

	mm->binfmt = new;
	if (new)
		__module_get(new->module);
}