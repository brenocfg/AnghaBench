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
struct TYPE_4__ {void* wanted_chars; int /*<<< orphan*/  getset_timeout_sup; void* set_char_sup; int /*<<< orphan*/  learning_timeout; void* cur_chars; void* sup_chars; } ;
struct TYPE_3__ {TYPE_2__ vnicc; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 void* QETH_VNICC_ALL ; 
 void* QETH_VNICC_DEFAULT ; 
 int /*<<< orphan*/  QETH_VNICC_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  QETH_VNICC_LEARNING ; 

__attribute__((used)) static void qeth_l2_vnicc_set_defaults(struct qeth_card *card)
{
	/* characteristics values */
	card->options.vnicc.sup_chars = QETH_VNICC_ALL;
	card->options.vnicc.cur_chars = QETH_VNICC_DEFAULT;
	card->options.vnicc.learning_timeout = QETH_VNICC_DEFAULT_TIMEOUT;
	/* supported commands */
	card->options.vnicc.set_char_sup = QETH_VNICC_ALL;
	card->options.vnicc.getset_timeout_sup = QETH_VNICC_LEARNING;
	/* settings wanted by users */
	card->options.vnicc.wanted_chars = QETH_VNICC_DEFAULT;
}