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
typedef  int /*<<< orphan*/  u8 ;
struct dlm_ctxt {int /*<<< orphan*/  dlm_join_events; int /*<<< orphan*/  joining_node; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __dlm_set_joining_node(struct dlm_ctxt *dlm,
					  u8 node)
{
	assert_spin_locked(&dlm->spinlock);

	dlm->joining_node = node;
	wake_up(&dlm->dlm_join_events);
}