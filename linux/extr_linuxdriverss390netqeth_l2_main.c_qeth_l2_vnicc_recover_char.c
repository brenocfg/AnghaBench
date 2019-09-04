#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int sup_chars; int set_char_sup; int wanted_chars; } ;
struct TYPE_4__ {TYPE_1__ vnicc; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */
 int IPA_VNICC_DISABLE ; 
 int IPA_VNICC_ENABLE ; 
 int QETH_VNICC_DEFAULT ; 
 int /*<<< orphan*/  qeth_l2_vnicc_set_char (struct qeth_card*,int,int) ; 

__attribute__((used)) static bool qeth_l2_vnicc_recover_char(struct qeth_card *card, u32 vnicc,
				       bool enable)
{
	u32 cmd = enable ? IPA_VNICC_ENABLE : IPA_VNICC_DISABLE;

	if (card->options.vnicc.sup_chars & vnicc &&
	    card->options.vnicc.set_char_sup & vnicc &&
	    !qeth_l2_vnicc_set_char(card, vnicc, cmd))
		return false;
	card->options.vnicc.wanted_chars &= ~vnicc;
	card->options.vnicc.wanted_chars |= QETH_VNICC_DEFAULT & vnicc;
	return true;
}