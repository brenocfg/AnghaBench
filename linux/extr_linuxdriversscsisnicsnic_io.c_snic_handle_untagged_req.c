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
struct snic_req_info {int /*<<< orphan*/  list; } ;
struct snic {int /*<<< orphan*/  spl_cmd_lock; int /*<<< orphan*/  spl_cmd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snic_handle_untagged_req(struct snic *snic, struct snic_req_info *rqi)
{
	unsigned long flags;

	INIT_LIST_HEAD(&rqi->list);

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	list_add_tail(&rqi->list, &snic->spl_cmd_list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
}