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
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_super; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SC_UNCLOSED ; 
 int /*<<< orphan*/  nilfs_segctor_construct (struct nilfs_sc_info*,int) ; 
 int /*<<< orphan*/  nilfs_segctor_start_timer (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_transaction_lock (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_segctor_thread_construct(struct nilfs_sc_info *sci, int mode)
{
	struct nilfs_transaction_info ti;

	nilfs_transaction_lock(sci->sc_super, &ti, 0);
	nilfs_segctor_construct(sci, mode);

	/*
	 * Unclosed segment should be retried.  We do this using sc_timer.
	 * Timeout of sc_timer will invoke complete construction which leads
	 * to close the current logical segment.
	 */
	if (test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags))
		nilfs_segctor_start_timer(sci);

	nilfs_transaction_unlock(sci->sc_super);
}