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
struct dlm_lock_resource {int state; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_migration_can_proceed(struct dlm_ctxt *dlm,
				     struct dlm_lock_resource *res,
				     u8 mig_target)
{
	int can_proceed;
	spin_lock(&res->spinlock);
	can_proceed = !!(res->state & DLM_LOCK_RES_MIGRATING);
	spin_unlock(&res->spinlock);

	/* target has died, so make the caller break out of the
	 * wait_event, but caller must recheck the domain_map */
	spin_lock(&dlm->spinlock);
	if (!test_bit(mig_target, dlm->domain_map))
		can_proceed = 1;
	spin_unlock(&dlm->spinlock);
	return can_proceed;
}