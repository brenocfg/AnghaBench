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
struct nilfs_sc_info {int sc_flush_request; int /*<<< orphan*/  sc_state_lock; int /*<<< orphan*/  sc_wait_daemon; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_segctor_do_flush(struct nilfs_sc_info *sci, int bn)
{
	spin_lock(&sci->sc_state_lock);
	if (!(sci->sc_flush_request & BIT(bn))) {
		unsigned long prev_req = sci->sc_flush_request;

		sci->sc_flush_request |= BIT(bn);
		if (!prev_req)
			wake_up(&sci->sc_wait_daemon);
	}
	spin_unlock(&sci->sc_state_lock);
}