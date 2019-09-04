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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sdu {int /*<<< orphan*/  nic_type; } ;
struct phy_dev {struct net_device** dev; int /*<<< orphan*/  priv_dev; int /*<<< orphan*/  (* get_endian ) (int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
struct hci_pdn_table_ind {int /*<<< orphan*/  nic_type; } ;
struct hci_packet {scalar_t__ data; int /*<<< orphan*/  cmd_evt; } ;
struct hci_connect_ind {int /*<<< orphan*/  connect; } ;

/* Variables and functions */
#define  LTE_LINK_ON_OFF_INDICATION 131 
#define  LTE_PDN_TABLE_IND 130 
#define  LTE_RX_MULTI_SDU 129 
#define  LTE_RX_SDU 128 
 int find_dev_index (int /*<<< orphan*/ ) ; 
 int gdm_dev16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdm_dev32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdm_lte_event_send (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  gdm_lte_multi_sdu_pkt (struct phy_dev*,char*,int) ; 
 int /*<<< orphan*/  gdm_lte_netif_rx (struct net_device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdm_lte_pdn_table (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdm_lte_receive_pkt(struct phy_dev *phy_dev, char *buf, int len)
{
	struct hci_packet *hci = (struct hci_packet *)buf;
	struct hci_pdn_table_ind *pdn_table = (struct hci_pdn_table_ind *)buf;
	struct sdu *sdu;
	struct net_device *dev;
	u8 endian = phy_dev->get_endian(phy_dev->priv_dev);
	int ret = 0;
	u16 cmd_evt;
	u32 nic_type;
	int index;

	if (!len)
		return ret;

	cmd_evt = gdm_dev16_to_cpu(endian, hci->cmd_evt);

	dev = phy_dev->dev[0];
	if (!dev)
		return 0;

	switch (cmd_evt) {
	case LTE_RX_SDU:
		sdu = (struct sdu *)hci->data;
		nic_type = gdm_dev32_to_cpu(endian, sdu->nic_type);
		index = find_dev_index(nic_type);
		if (index < 0)
			return index;
		dev = phy_dev->dev[index];
		gdm_lte_netif_rx(dev, hci->data, len, nic_type);
		break;
	case LTE_RX_MULTI_SDU:
		gdm_lte_multi_sdu_pkt(phy_dev, buf, len);
		break;
	case LTE_LINK_ON_OFF_INDICATION:
		netdev_info(dev, "link %s\n",
			    ((struct hci_connect_ind *)buf)->connect
			    ? "on" : "off");
		break;
	case LTE_PDN_TABLE_IND:
		pdn_table = (struct hci_pdn_table_ind *)buf;
		nic_type = gdm_dev32_to_cpu(endian, pdn_table->nic_type);
		index = find_dev_index(nic_type);
		if (index < 0)
			return index;
		dev = phy_dev->dev[index];
		gdm_lte_pdn_table(dev, buf, len);
		/* Fall through */
	default:
		ret = gdm_lte_event_send(dev, buf, len);
		break;
	}

	return ret;
}