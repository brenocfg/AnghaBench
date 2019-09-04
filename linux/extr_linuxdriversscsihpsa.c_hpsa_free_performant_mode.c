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
struct ctlr_info {int /*<<< orphan*/ * blockFetchTable; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsa_free_ioaccel1_cmd_and_bft (struct ctlr_info*) ; 
 int /*<<< orphan*/  hpsa_free_ioaccel2_cmd_and_bft (struct ctlr_info*) ; 
 int /*<<< orphan*/  hpsa_free_reply_queues (struct ctlr_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_free_performant_mode(struct ctlr_info *h)
{
	kfree(h->blockFetchTable);
	h->blockFetchTable = NULL;
	hpsa_free_reply_queues(h);
	hpsa_free_ioaccel1_cmd_and_bft(h);
	hpsa_free_ioaccel2_cmd_and_bft(h);
}