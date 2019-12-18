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
struct TYPE_2__ {int /*<<< orphan*/ * xol_area; } ;
struct mm_struct {TYPE_1__ uprobes_state; } ;

/* Variables and functions */

__attribute__((used)) static void mm_init_uprobes_state(struct mm_struct *mm)
{
#ifdef CONFIG_UPROBES
	mm->uprobes_state.xol_area = NULL;
#endif
}