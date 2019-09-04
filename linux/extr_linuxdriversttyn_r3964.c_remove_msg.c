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
struct r3964_message {scalar_t__ block; struct r3964_message* next; } ;
struct r3964_info {int dummy; } ;
struct r3964_client_info {int /*<<< orphan*/  lock; scalar_t__ next_block_to_read; int /*<<< orphan*/  msg_count; int /*<<< orphan*/ * last_msg; struct r3964_message* first_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_client_block (struct r3964_info*,struct r3964_client_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct r3964_message *remove_msg(struct r3964_info *pInfo,
					struct r3964_client_info *pClient)
{
	struct r3964_message *pMsg = NULL;
	unsigned long flags;

	if (pClient->first_msg) {
		spin_lock_irqsave(&pClient->lock, flags);

		pMsg = pClient->first_msg;
		pClient->first_msg = pMsg->next;
		if (pClient->first_msg == NULL) {
			pClient->last_msg = NULL;
		}

		pClient->msg_count--;
		if (pMsg->block) {
			remove_client_block(pInfo, pClient);
			pClient->next_block_to_read = pMsg->block;
		}
		spin_unlock_irqrestore(&pClient->lock, flags);
	}
	return pMsg;
}