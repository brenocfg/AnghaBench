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
struct pppoatm_vcc {int /*<<< orphan*/  inflight; int /*<<< orphan*/  atmvcc; int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED ; 
 scalar_t__ atm_may_send (int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pppoatm_may_send(struct pppoatm_vcc *pvcc, int size)
{
	/*
	 * It's not clear that we need to bother with using atm_may_send()
	 * to check we don't exceed sk->sk_sndbuf. If userspace sets a
	 * value of sk_sndbuf which is lower than the MTU, we're going to
	 * block for ever. But the code always did that before we introduced
	 * the packet count limit, so...
	 */
	if (atm_may_send(pvcc->atmvcc, size) &&
	    atomic_inc_not_zero(&pvcc->inflight))
		return 1;

	/*
	 * We use test_and_set_bit() rather than set_bit() here because
	 * we need to ensure there's a memory barrier after it. The bit
	 * *must* be set before we do the atomic_inc() on pvcc->inflight.
	 * There's no smp_mb__after_set_bit(), so it's this or abuse
	 * smp_mb__after_atomic().
	 */
	test_and_set_bit(BLOCKED, &pvcc->blocked);

	/*
	 * We may have raced with pppoatm_pop(). If it ran for the
	 * last packet in the queue, *just* before we set the BLOCKED
	 * bit, then it might never run again and the channel could
	 * remain permanently blocked. Cope with that race by checking
	 * *again*. If it did run in that window, we'll have space on
	 * the queue now and can return success. It's harmless to leave
	 * the BLOCKED flag set, since it's only used as a trigger to
	 * run the wakeup tasklet. Another wakeup will never hurt.
	 * If pppoatm_pop() is running but hasn't got as far as making
	 * space on the queue yet, then it hasn't checked the BLOCKED
	 * flag yet either, so we're safe in that case too. It'll issue
	 * an "immediate" wakeup... where "immediate" actually involves
	 * taking the PPP channel's ->downl lock, which is held by the
	 * code path that calls pppoatm_send(), and is thus going to
	 * wait for us to finish.
	 */
	if (atm_may_send(pvcc->atmvcc, size) &&
	    atomic_inc_not_zero(&pvcc->inflight))
		return 1;

	return 0;
}