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
struct sk_buff {int dummy; } ;
struct pppoatm_vcc {int /*<<< orphan*/  wakeup_tasklet; int /*<<< orphan*/  blocked; int /*<<< orphan*/  inflight; int /*<<< orphan*/  (* old_pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED ; 
 struct pppoatm_vcc* atmvcc_to_pvcc (struct atm_vcc*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppoatm_pop(struct atm_vcc *atmvcc, struct sk_buff *skb)
{
	struct pppoatm_vcc *pvcc = atmvcc_to_pvcc(atmvcc);

	pvcc->old_pop(atmvcc, skb);
	atomic_dec(&pvcc->inflight);

	/*
	 * We always used to run the wakeup tasklet unconditionally here, for
	 * fear of race conditions where we clear the BLOCKED flag just as we
	 * refuse another packet in pppoatm_send(). This was quite inefficient.
	 *
	 * In fact it's OK. The PPP core will only ever call pppoatm_send()
	 * while holding the channel->downl lock. And ppp_output_wakeup() as
	 * called by the tasklet will *also* grab that lock. So even if another
	 * CPU is in pppoatm_send() right now, the tasklet isn't going to race
	 * with it. The wakeup *will* happen after the other CPU is safely out
	 * of pppoatm_send() again.
	 *
	 * So if the CPU in pppoatm_send() has already set the BLOCKED bit and
	 * it about to return, that's fine. We trigger a wakeup which will
	 * happen later. And if the CPU in pppoatm_send() *hasn't* set the
	 * BLOCKED bit yet, that's fine too because of the double check in
	 * pppoatm_may_send() which is commented there.
	 */
	if (test_and_clear_bit(BLOCKED, &pvcc->blocked))
		tasklet_schedule(&pvcc->wakeup_tasklet);
}