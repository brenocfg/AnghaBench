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
struct rio_channel {int state; int /*<<< orphan*/  lock; } ;
typedef  enum rio_cm_state { ____Placeholder_rio_cm_state } rio_cm_state ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riocm_cmp_exch(struct rio_channel *ch,
			   enum rio_cm_state cmp, enum rio_cm_state exch)
{
	int ret;

	spin_lock_bh(&ch->lock);
	ret = (ch->state == cmp);
	if (ret)
		ch->state = exch;
	spin_unlock_bh(&ch->lock);
	return ret;
}