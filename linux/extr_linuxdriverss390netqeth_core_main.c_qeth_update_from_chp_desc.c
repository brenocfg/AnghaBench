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
struct TYPE_5__ {scalar_t__ type; scalar_t__ func_level; } ;
struct TYPE_4__ {scalar_t__ no_out_queues; } ;
struct TYPE_6__ {struct ccw_device* ccwdev; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ qdio; TYPE_3__ data; } ;
struct channel_path_desc_fmt0 {int chpp; scalar_t__ desc; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  SETUP ; 
 struct channel_path_desc_fmt0* ccw_device_get_chp_desc (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct channel_path_desc_fmt0*) ; 
 int /*<<< orphan*/  qeth_set_multiple_write_queues (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_set_single_write_queues (struct qeth_card*) ; 

__attribute__((used)) static void qeth_update_from_chp_desc(struct qeth_card *card)
{
	struct ccw_device *ccwdev;
	struct channel_path_desc_fmt0 *chp_dsc;

	QETH_DBF_TEXT(SETUP, 2, "chp_desc");

	ccwdev = card->data.ccwdev;
	chp_dsc = ccw_device_get_chp_desc(ccwdev, 0);
	if (!chp_dsc)
		goto out;

	card->info.func_level = 0x4100 + chp_dsc->desc;
	if (card->info.type == QETH_CARD_TYPE_IQD)
		goto out;

	/* CHPP field bit 6 == 1 -> single queue */
	if ((chp_dsc->chpp & 0x02) == 0x02)
		qeth_set_single_write_queues(card);
	else
		qeth_set_multiple_write_queues(card);
out:
	kfree(chp_dsc);
	QETH_DBF_TEXT_(SETUP, 2, "nr:%x", card->qdio.no_out_queues);
	QETH_DBF_TEXT_(SETUP, 2, "lvl:%02x", card->info.func_level);
}