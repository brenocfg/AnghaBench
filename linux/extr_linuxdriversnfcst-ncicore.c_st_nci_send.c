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
struct st_nci_info {int /*<<< orphan*/  ndlc; int /*<<< orphan*/  flags; } ;
struct sk_buff {void* dev; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ST_NCI_RUNNING ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int ndlc_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_nci_send(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	skb->dev = (void *)ndev;

	if (!test_bit(ST_NCI_RUNNING, &info->flags))
		return -EBUSY;

	return ndlc_send(info->ndlc, skb);
}