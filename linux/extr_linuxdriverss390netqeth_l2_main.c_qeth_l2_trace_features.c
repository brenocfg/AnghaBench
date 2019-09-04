#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sup_chars; } ;
struct TYPE_4__ {int /*<<< orphan*/  supported_funcs; } ;
struct TYPE_6__ {TYPE_2__ vnicc; TYPE_1__ sbp; } ;
struct qeth_card {TYPE_3__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

__attribute__((used)) static void qeth_l2_trace_features(struct qeth_card *card)
{
	/* Set BridgePort features */
	QETH_CARD_TEXT(card, 2, "featuSBP");
	QETH_CARD_HEX(card, 2, &card->options.sbp.supported_funcs,
		      sizeof(card->options.sbp.supported_funcs));
	/* VNIC Characteristics features */
	QETH_CARD_TEXT(card, 2, "feaVNICC");
	QETH_CARD_HEX(card, 2, &card->options.vnicc.sup_chars,
		      sizeof(card->options.vnicc.sup_chars));
}