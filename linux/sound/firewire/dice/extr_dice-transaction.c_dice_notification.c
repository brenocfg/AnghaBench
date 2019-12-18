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
typedef  int u32 ;
struct snd_dice {int notification_bits; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  clock_accepted; int /*<<< orphan*/  lock; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int NOTIFY_LOCK_CHG ; 
 int /*<<< orphan*/  RCODE_ADDRESS_ERROR ; 
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 int /*<<< orphan*/  RCODE_TYPE_ERROR ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int be32_to_cpup (void*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dice_notification(struct fw_card *card, struct fw_request *request,
			      int tcode, int destination, int source,
			      int generation, unsigned long long offset,
			      void *data, size_t length, void *callback_data)
{
	struct snd_dice *dice = callback_data;
	u32 bits;
	unsigned long flags;

	if (tcode != TCODE_WRITE_QUADLET_REQUEST) {
		fw_send_response(card, request, RCODE_TYPE_ERROR);
		return;
	}
	if ((offset & 3) != 0) {
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
		return;
	}

	bits = be32_to_cpup(data);

	spin_lock_irqsave(&dice->lock, flags);
	dice->notification_bits |= bits;
	spin_unlock_irqrestore(&dice->lock, flags);

	fw_send_response(card, request, RCODE_COMPLETE);

	if (bits & NOTIFY_LOCK_CHG)
		complete(&dice->clock_accepted);
	wake_up(&dice->hwdep_wait);
}