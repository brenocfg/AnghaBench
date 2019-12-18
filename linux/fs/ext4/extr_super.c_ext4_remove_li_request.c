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
struct ext4_sb_info {int /*<<< orphan*/ * s_li_request; } ;
struct ext4_li_request {int /*<<< orphan*/  lr_request; struct ext4_sb_info* lr_sbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ext4_li_request*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_remove_li_request(struct ext4_li_request *elr)
{
	struct ext4_sb_info *sbi;

	if (!elr)
		return;

	sbi = elr->lr_sbi;

	list_del(&elr->lr_request);
	sbi->s_li_request = NULL;
	kfree(elr);
}