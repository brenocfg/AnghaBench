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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int /*<<< orphan*/  write; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  __ipa_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_osn_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int) ; 
 struct qeth_cmd_buffer* qeth_wait_for_buffer (int /*<<< orphan*/ *) ; 

int qeth_osn_assist(struct net_device *dev, void *data, int data_len)
{
	struct qeth_cmd_buffer *iob;
	struct qeth_card *card;

	if (!dev)
		return -ENODEV;
	card = dev->ml_priv;
	if (!card)
		return -ENODEV;
	QETH_CARD_TEXT(card, 2, "osnsdmc");
	if (!qeth_card_hw_is_reachable(card))
		return -ENODEV;
	iob = qeth_wait_for_buffer(&card->write);
	memcpy(__ipa_cmd(iob), data, data_len);
	return qeth_osn_send_ipa_cmd(card, iob, data_len);
}