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
typedef  size_t u8 ;
struct mwifiex_wmm_desc {size_t* queue_priority; int /*<<< orphan*/  highest_queued_prio; } ;
struct mwifiex_private {size_t* tos_to_tid_inv; struct mwifiex_wmm_desc wmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGH_PRIO_TID ; 
 int MAX_NUM_TID ; 
 size_t** ac_to_tid ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t* tos_to_tid ; 

__attribute__((used)) static void
mwifiex_wmm_queue_priorities_tid(struct mwifiex_private *priv)
{
	struct mwifiex_wmm_desc *wmm = &priv->wmm;
	u8 *queue_priority = wmm->queue_priority;
	int i;

	for (i = 0; i < 4; ++i) {
		tos_to_tid[7 - (i * 2)] = ac_to_tid[queue_priority[i]][1];
		tos_to_tid[6 - (i * 2)] = ac_to_tid[queue_priority[i]][0];
	}

	for (i = 0; i < MAX_NUM_TID; ++i)
		priv->tos_to_tid_inv[tos_to_tid[i]] = (u8)i;

	atomic_set(&wmm->highest_queued_prio, HIGH_PRIO_TID);
}