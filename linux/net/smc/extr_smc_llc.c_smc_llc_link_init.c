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
typedef  int /*<<< orphan*/  u32 ;
struct smc_link_group {scalar_t__ id; } ;
struct smc_link {int /*<<< orphan*/  llc_testlink_wrk; int /*<<< orphan*/  llc_testlink_resp; int /*<<< orphan*/  llc_delete_rkey_mutex; int /*<<< orphan*/  llc_delete_rkey; int /*<<< orphan*/  llc_confirm_rkey; int /*<<< orphan*/  llc_add_resp; int /*<<< orphan*/  llc_add; int /*<<< orphan*/  llc_confirm_resp; int /*<<< orphan*/  llc_confirm; int /*<<< orphan*/  llc_wq; int /*<<< orphan*/  link_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 
 int /*<<< orphan*/  smc_llc_testlink_work ; 

int smc_llc_link_init(struct smc_link *link)
{
	struct smc_link_group *lgr = smc_get_lgr(link);
	link->llc_wq = alloc_ordered_workqueue("llc_wq-%x:%x)", WQ_MEM_RECLAIM,
					       *((u32 *)lgr->id),
					       link->link_id);
	if (!link->llc_wq)
		return -ENOMEM;
	init_completion(&link->llc_confirm);
	init_completion(&link->llc_confirm_resp);
	init_completion(&link->llc_add);
	init_completion(&link->llc_add_resp);
	init_completion(&link->llc_confirm_rkey);
	init_completion(&link->llc_delete_rkey);
	mutex_init(&link->llc_delete_rkey_mutex);
	init_completion(&link->llc_testlink_resp);
	INIT_DELAYED_WORK(&link->llc_testlink_wrk, smc_llc_testlink_work);
	return 0;
}