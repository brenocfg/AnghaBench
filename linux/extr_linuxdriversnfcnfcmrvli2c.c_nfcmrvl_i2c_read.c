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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nfcmrvl_i2c_drv_data {TYPE_2__* i2c; TYPE_1__* priv; } ;
struct nci_ctrl_hdr {int plen; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NCI_CTRL_HDR_SIZE ; 
 int NCI_MAX_PAYLOAD_SIZE ; 
 int i2c_master_recv (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nci_skb_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct nci_ctrl_hdr*,int) ; 

__attribute__((used)) static int nfcmrvl_i2c_read(struct nfcmrvl_i2c_drv_data *drv_data,
			    struct sk_buff **skb)
{
	int ret;
	struct nci_ctrl_hdr nci_hdr;

	/* Read NCI header to know the payload size */
	ret = i2c_master_recv(drv_data->i2c, (u8 *)&nci_hdr, NCI_CTRL_HDR_SIZE);
	if (ret != NCI_CTRL_HDR_SIZE) {
		nfc_err(&drv_data->i2c->dev, "cannot read NCI header\n");
		return -EBADMSG;
	}

	if (nci_hdr.plen > NCI_MAX_PAYLOAD_SIZE) {
		nfc_err(&drv_data->i2c->dev, "invalid packet payload size\n");
		return -EBADMSG;
	}

	*skb = nci_skb_alloc(drv_data->priv->ndev,
			     nci_hdr.plen + NCI_CTRL_HDR_SIZE, GFP_KERNEL);
	if (!*skb)
		return -ENOMEM;

	/* Copy NCI header into the SKB */
	skb_put_data(*skb, &nci_hdr, NCI_CTRL_HDR_SIZE);

	if (nci_hdr.plen) {
		/* Read the NCI payload */
		ret = i2c_master_recv(drv_data->i2c,
				      skb_put(*skb, nci_hdr.plen),
				      nci_hdr.plen);

		if (ret != nci_hdr.plen) {
			nfc_err(&drv_data->i2c->dev,
				"Invalid frame payload length: %u (expected %u)\n",
				ret, nci_hdr.plen);
			kfree_skb(*skb);
			return -EBADMSG;
		}
	}

	return 0;
}