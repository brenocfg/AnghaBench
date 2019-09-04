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
struct wcn36xx_dxe_ctl {struct wcn36xx_dxe_ctl* next; } ;
struct wcn36xx_dxe_ch {int desc_num; struct wcn36xx_dxe_ctl* head_blk_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wcn36xx_dxe_ctl*) ; 

__attribute__((used)) static void wcn36xx_dxe_free_ctl_block(struct wcn36xx_dxe_ch *ch)
{
	struct wcn36xx_dxe_ctl *ctl = ch->head_blk_ctl, *next;
	int i;

	for (i = 0; i < ch->desc_num && ctl; i++) {
		next = ctl->next;
		kfree(ctl);
		ctl = next;
	}
}