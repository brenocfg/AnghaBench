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
struct TYPE_2__ {int /*<<< orphan*/  sp_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_STACK_PLUGIN_O2CB ; 
 TYPE_1__* active_stack ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline int ocfs2_is_o2cb_active(void)
{
	return !strcmp(active_stack->sp_name, OCFS2_STACK_PLUGIN_O2CB);
}