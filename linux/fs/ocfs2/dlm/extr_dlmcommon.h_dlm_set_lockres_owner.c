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
struct dlm_lock_resource {int /*<<< orphan*/  owner; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dlm_set_lockres_owner(struct dlm_ctxt *dlm,
					 struct dlm_lock_resource *res,
					 u8 owner)
{
	assert_spin_locked(&res->spinlock);

	res->owner = owner;
}