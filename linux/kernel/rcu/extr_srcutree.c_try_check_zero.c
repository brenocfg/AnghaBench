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
struct srcu_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRCU_RETRY_CHECK_DELAY ; 
 int /*<<< orphan*/  srcu_get_delay (struct srcu_struct*) ; 
 scalar_t__ srcu_readers_active_idx_check (struct srcu_struct*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool try_check_zero(struct srcu_struct *ssp, int idx, int trycount)
{
	for (;;) {
		if (srcu_readers_active_idx_check(ssp, idx))
			return true;
		if (--trycount + !srcu_get_delay(ssp) <= 0)
			return false;
		udelay(SRCU_RETRY_CHECK_DELAY);
	}
}