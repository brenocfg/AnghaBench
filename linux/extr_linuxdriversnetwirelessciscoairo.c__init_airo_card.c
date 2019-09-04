#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int device; } ;
struct net_device {unsigned short irq; int base_addr; char* name; struct airo_info* ml_priv; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  priv_flags; TYPE_3__* wireless_data; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * netdev_ops; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * spy_data; } ;
struct TYPE_7__ {int len; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct airo_info {int flags; int wep_capable; int max_wep_idx; int bssListRidLen; struct pci_dev* pci; int /*<<< orphan*/  pcimem; int /*<<< orphan*/  pciaux; int /*<<< orphan*/  shared_dma; int /*<<< orphan*/  shared; struct net_device* wifidev; int /*<<< orphan*/ * fids; int /*<<< orphan*/  bssListNext; int /*<<< orphan*/  bssListFirst; struct net_device* dev; int /*<<< orphan*/  bap_read; TYPE_3__ wireless_data; int /*<<< orphan*/  spy_data; int /*<<< orphan*/  txq; TYPE_2__ APList; int /*<<< orphan*/ * tfm; int /*<<< orphan*/  thr_wait; TYPE_1__ config; int /*<<< orphan*/  sem; int /*<<< orphan*/  aux_lock; scalar_t__ jobs; } ;
struct APListRid {int dummy; } ;
struct TYPE_9__ {int softCap; int /*<<< orphan*/  softSubVer; int /*<<< orphan*/  softVer; } ;
typedef  TYPE_4__ CapabilityRid ;
typedef  int /*<<< orphan*/  BSSListRidExtra ;
typedef  int /*<<< orphan*/  BSSListRid ;

/* Variables and functions */
 int /*<<< orphan*/  AIRO_DEF_MTU ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int FLAG_RADIO_DOWN ; 
 int /*<<< orphan*/  FLAG_REGISTERED ; 
 int /*<<< orphan*/  FLAG_WPA_CAPABLE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int MAX_FIDS ; 
 int /*<<< orphan*/  MIC_MSGLEN_MAX ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  PCI_SHARED_LEN ; 
 int /*<<< orphan*/  RID_BSSLISTFIRST ; 
 int /*<<< orphan*/  RID_BSSLISTNEXT ; 
 int /*<<< orphan*/  RID_WPA_BSSLISTFIRST ; 
 int /*<<< orphan*/  RID_WPA_BSSLISTNEXT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  add_airo_dev (struct airo_info*) ; 
 int /*<<< orphan*/  airo_handler_def ; 
 int /*<<< orphan*/  airo_netdev_ops ; 
 scalar_t__ airo_networks_allocate (struct airo_info*) ; 
 int /*<<< orphan*/  airo_networks_free (struct airo_info*) ; 
 int /*<<< orphan*/  airo_networks_initialize (struct airo_info*) ; 
 int /*<<< orphan*/  airo_print_dbg (char*,char*) ; 
 int /*<<< orphan*/  airo_print_err (char*,char*) ; 
 int /*<<< orphan*/  airo_print_info (char*,char*,...) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int) ; 
 int /*<<< orphan*/  del_airo_dev (struct airo_info*) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  fast_bap_read ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct net_device* init_wifidev (struct airo_info*,struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_map_card (struct airo_info*,struct pci_dev*) ; 
 int /*<<< orphan*/  mpi_netdev_ops ; 
 int /*<<< orphan*/  mpi_unmap_card (struct pci_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct airo_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ probe ; 
 int readCapabilityRid (struct airo_info*,TYPE_4__*,int) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_card (struct net_device*,int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int setup_card (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setup_proc_entry (struct net_device*,struct airo_info*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  transmit_allocate (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static struct net_device *_init_airo_card( unsigned short irq, int port,
					   int is_pcmcia, struct pci_dev *pci,
					   struct device *dmdev )
{
	struct net_device *dev;
	struct airo_info *ai;
	int i, rc;
	CapabilityRid cap_rid;

	/* Create the network device object. */
	dev = alloc_netdev(sizeof(*ai), "", NET_NAME_UNKNOWN, ether_setup);
	if (!dev) {
		airo_print_err("", "Couldn't alloc_etherdev");
		return NULL;
	}

	ai = dev->ml_priv = netdev_priv(dev);
	ai->wifidev = NULL;
	ai->flags = 1 << FLAG_RADIO_DOWN;
	ai->jobs = 0;
	ai->dev = dev;
	if (pci && (pci->device == 0x5000 || pci->device == 0xa504)) {
		airo_print_dbg("", "Found an MPI350 card");
		set_bit(FLAG_MPI, &ai->flags);
	}
	spin_lock_init(&ai->aux_lock);
	sema_init(&ai->sem, 1);
	ai->config.len = 0;
	ai->pci = pci;
	init_waitqueue_head (&ai->thr_wait);
	ai->tfm = NULL;
	add_airo_dev(ai);
	ai->APList.len = cpu_to_le16(sizeof(struct APListRid));

	if (airo_networks_allocate (ai))
		goto err_out_free;
	airo_networks_initialize (ai);

	skb_queue_head_init (&ai->txq);

	/* The Airo-specific entries in the device structure. */
	if (test_bit(FLAG_MPI,&ai->flags))
		dev->netdev_ops = &mpi_netdev_ops;
	else
		dev->netdev_ops = &airo_netdev_ops;
	dev->wireless_handlers = &airo_handler_def;
	ai->wireless_data.spy_data = &ai->spy_data;
	dev->wireless_data = &ai->wireless_data;
	dev->irq = irq;
	dev->base_addr = port;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->max_mtu = MIC_MSGLEN_MAX;

	SET_NETDEV_DEV(dev, dmdev);

	reset_card (dev, 1);
	msleep(400);

	if (!is_pcmcia) {
		if (!request_region(dev->base_addr, 64, DRV_NAME)) {
			rc = -EBUSY;
			airo_print_err(dev->name, "Couldn't request region");
			goto err_out_nets;
		}
	}

	if (test_bit(FLAG_MPI,&ai->flags)) {
		if (mpi_map_card(ai, pci)) {
			airo_print_err("", "Could not map memory");
			goto err_out_res;
		}
	}

	if (probe) {
		if (setup_card(ai, dev->dev_addr, 1) != SUCCESS) {
			airo_print_err(dev->name, "MAC could not be enabled" );
			rc = -EIO;
			goto err_out_map;
		}
	} else if (!test_bit(FLAG_MPI,&ai->flags)) {
		ai->bap_read = fast_bap_read;
		set_bit(FLAG_FLASHING, &ai->flags);
	}

	strcpy(dev->name, "eth%d");
	rc = register_netdev(dev);
	if (rc) {
		airo_print_err(dev->name, "Couldn't register_netdev");
		goto err_out_map;
	}
	ai->wifidev = init_wifidev(ai, dev);
	if (!ai->wifidev)
		goto err_out_reg;

	rc = readCapabilityRid(ai, &cap_rid, 1);
	if (rc != SUCCESS) {
		rc = -EIO;
		goto err_out_wifi;
	}
	/* WEP capability discovery */
	ai->wep_capable = (cap_rid.softCap & cpu_to_le16(0x02)) ? 1 : 0;
	ai->max_wep_idx = (cap_rid.softCap & cpu_to_le16(0x80)) ? 3 : 0;

	airo_print_info(dev->name, "Firmware version %x.%x.%02d",
	                ((le16_to_cpu(cap_rid.softVer) >> 8) & 0xF),
	                (le16_to_cpu(cap_rid.softVer) & 0xFF),
	                le16_to_cpu(cap_rid.softSubVer));

	/* Test for WPA support */
	/* Only firmware versions 5.30.17 or better can do WPA */
	if (le16_to_cpu(cap_rid.softVer) > 0x530
	 || (le16_to_cpu(cap_rid.softVer) == 0x530
	      && le16_to_cpu(cap_rid.softSubVer) >= 17)) {
		airo_print_info(ai->dev->name, "WPA supported.");

		set_bit(FLAG_WPA_CAPABLE, &ai->flags);
		ai->bssListFirst = RID_WPA_BSSLISTFIRST;
		ai->bssListNext = RID_WPA_BSSLISTNEXT;
		ai->bssListRidLen = sizeof(BSSListRid);
	} else {
		airo_print_info(ai->dev->name, "WPA unsupported with firmware "
			"versions older than 5.30.17.");

		ai->bssListFirst = RID_BSSLISTFIRST;
		ai->bssListNext = RID_BSSLISTNEXT;
		ai->bssListRidLen = sizeof(BSSListRid) - sizeof(BSSListRidExtra);
	}

	set_bit(FLAG_REGISTERED,&ai->flags);
	airo_print_info(dev->name, "MAC enabled %pM", dev->dev_addr);

	/* Allocate the transmit buffers */
	if (probe && !test_bit(FLAG_MPI,&ai->flags))
		for( i = 0; i < MAX_FIDS; i++ )
			ai->fids[i] = transmit_allocate(ai,AIRO_DEF_MTU,i>=MAX_FIDS/2);

	if (setup_proc_entry(dev, dev->ml_priv) < 0)
		goto err_out_wifi;

	return dev;

err_out_wifi:
	unregister_netdev(ai->wifidev);
	free_netdev(ai->wifidev);
err_out_reg:
	unregister_netdev(dev);
err_out_map:
	if (test_bit(FLAG_MPI,&ai->flags) && pci) {
		pci_free_consistent(pci, PCI_SHARED_LEN, ai->shared, ai->shared_dma);
		iounmap(ai->pciaux);
		iounmap(ai->pcimem);
		mpi_unmap_card(ai->pci);
	}
err_out_res:
	if (!is_pcmcia)
	        release_region( dev->base_addr, 64 );
err_out_nets:
	airo_networks_free(ai);
err_out_free:
	del_airo_dev(ai);
	free_netdev(dev);
	return NULL;
}