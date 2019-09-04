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
struct qeth_card {int dummy; } ;
struct _qeth_l2_vnicc_request_cbctl {int /*<<< orphan*/  sub_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_VNICC_QUERY_CHARS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_l2_vnicc_request (struct qeth_card*,struct _qeth_l2_vnicc_request_cbctl*) ; 

__attribute__((used)) static int qeth_l2_vnicc_query_chars(struct qeth_card *card)
{
	struct _qeth_l2_vnicc_request_cbctl cbctl;

	/* prepare callback control */
	cbctl.sub_cmd = IPA_VNICC_QUERY_CHARS;

	QETH_CARD_TEXT(card, 2, "vniccqch");
	return qeth_l2_vnicc_request(card, &cbctl);
}