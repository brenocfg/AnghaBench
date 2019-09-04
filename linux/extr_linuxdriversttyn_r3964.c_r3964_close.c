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
struct tty_struct {struct r3964_message* disc_data; } ;
struct r3964_message {struct r3964_message* tx_buf; struct r3964_message* rx_buf; struct r3964_message* next; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_last; struct r3964_message* tx_first; int /*<<< orphan*/  pid; scalar_t__ msg_count; struct r3964_message* firstClient; int /*<<< orphan*/  tmr; } ;
struct r3964_info {struct r3964_info* tx_buf; struct r3964_info* rx_buf; struct r3964_info* next; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_last; struct r3964_info* tx_first; int /*<<< orphan*/  pid; scalar_t__ msg_count; struct r3964_info* firstClient; int /*<<< orphan*/  tmr; } ;
struct r3964_client_info {struct r3964_client_info* tx_buf; struct r3964_client_info* rx_buf; struct r3964_client_info* next; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_last; struct r3964_client_info* tx_first; int /*<<< orphan*/  pid; scalar_t__ msg_count; struct r3964_client_info* firstClient; int /*<<< orphan*/  tmr; } ;
struct r3964_block_header {struct r3964_block_header* tx_buf; struct r3964_block_header* rx_buf; struct r3964_block_header* next; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_last; struct r3964_block_header* tx_first; int /*<<< orphan*/  pid; scalar_t__ msg_count; struct r3964_block_header* firstClient; int /*<<< orphan*/  tmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_L (char*) ; 
 int /*<<< orphan*/  TRACE_M (char*,struct r3964_message*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r3964_message*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 struct r3964_message* remove_msg (struct r3964_message*,struct r3964_message*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void r3964_close(struct tty_struct *tty)
{
	struct r3964_info *pInfo = tty->disc_data;
	struct r3964_client_info *pClient, *pNext;
	struct r3964_message *pMsg;
	struct r3964_block_header *pHeader, *pNextHeader;
	unsigned long flags;

	TRACE_L("close");

	/*
	 * Make sure that our task queue isn't activated.  If it
	 * is, take it out of the linked list.
	 */
	del_timer_sync(&pInfo->tmr);

	/* Remove client-structs and message queues: */
	pClient = pInfo->firstClient;
	while (pClient) {
		pNext = pClient->next;
		while (pClient->msg_count) {
			pMsg = remove_msg(pInfo, pClient);
			if (pMsg) {
				kfree(pMsg);
				TRACE_M("r3964_close - msg kfree %p", pMsg);
			}
		}
		put_pid(pClient->pid);
		kfree(pClient);
		TRACE_M("r3964_close - client kfree %p", pClient);
		pClient = pNext;
	}
	/* Remove jobs from tx_queue: */
	spin_lock_irqsave(&pInfo->lock, flags);
	pHeader = pInfo->tx_first;
	pInfo->tx_first = pInfo->tx_last = NULL;
	spin_unlock_irqrestore(&pInfo->lock, flags);

	while (pHeader) {
		pNextHeader = pHeader->next;
		kfree(pHeader);
		pHeader = pNextHeader;
	}

	/* Free buffers: */
	kfree(pInfo->rx_buf);
	TRACE_M("r3964_close - rx_buf kfree %p", pInfo->rx_buf);
	kfree(pInfo->tx_buf);
	TRACE_M("r3964_close - tx_buf kfree %p", pInfo->tx_buf);
	kfree(pInfo);
	TRACE_M("r3964_close - info kfree %p", pInfo);
}