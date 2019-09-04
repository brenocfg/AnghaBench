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
typedef  int /*<<< orphan*/  u16 ;
struct qeth_vlan_vid {int /*<<< orphan*/  list; int /*<<< orphan*/  vid; } ;
struct qeth_card {int /*<<< orphan*/  vid_list_mutex; int /*<<< orphan*/  vid_list; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPA_CMD_SETVLAN ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  kfree (struct qeth_vlan_vid*) ; 
 struct qeth_vlan_vid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setdelvlan (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_vlan_rx_add_vid(struct net_device *dev,
				   __be16 proto, u16 vid)
{
	struct qeth_card *card = dev->ml_priv;
	struct qeth_vlan_vid *id;
	int rc;

	QETH_CARD_TEXT_(card, 4, "aid:%d", vid);
	if (!vid)
		return 0;
	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_CARD_TEXT(card, 3, "aidREC");
		return 0;
	}
	id = kmalloc(sizeof(*id), GFP_KERNEL);
	if (id) {
		id->vid = vid;
		rc = qeth_l2_send_setdelvlan(card, vid, IPA_CMD_SETVLAN);
		if (rc) {
			kfree(id);
			return rc;
		}
		mutex_lock(&card->vid_list_mutex);
		list_add_tail(&id->list, &card->vid_list);
		mutex_unlock(&card->vid_list_mutex);
	} else {
		return -ENOMEM;
	}
	return 0;
}