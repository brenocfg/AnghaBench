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
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcdDevice; scalar_t__ bDescriptorType; scalar_t__ bLength; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; int /*<<< orphan*/  devnum; } ;
struct net_device {int mtu; int name; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
struct TYPE_4__ {int statistics_mask; int max_multicast_filters; int hw_addr; int /*<<< orphan*/  segment_size; } ;
struct kaweth_device {void* tx_urb; void* rx_urb; void* irq_urb; int /*<<< orphan*/  intbufferhandle; void* intbuffer; struct usb_device* dev; int /*<<< orphan*/  rxbufferhandle; void* rx_buf; struct net_device* net; int /*<<< orphan*/  lowmem_work; TYPE_2__ configuration; int /*<<< orphan*/ * firmware_buf; int /*<<< orphan*/  term_wait; int /*<<< orphan*/  device_lock; struct usb_interface* intf; } ;
typedef  int eth_addr_t ;
typedef  int /*<<< orphan*/  bcast_addr ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTBUFFERSIZE ; 
 int /*<<< orphan*/  KAWETH_BUF_SIZE ; 
 int KAWETH_PACKET_FILTER_BROADCAST ; 
 int KAWETH_PACKET_FILTER_DIRECTED ; 
 int KAWETH_PACKET_FILTER_MULTICAST ; 
 int /*<<< orphan*/  KAWETH_SOFS_TO_WAIT ; 
 int /*<<< orphan*/  KAWETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int kaweth_download_firmware (struct kaweth_device*,char*,int,int) ; 
 int /*<<< orphan*/  kaweth_netdev_ops ; 
 int kaweth_read_configuration (struct kaweth_device*) ; 
 int /*<<< orphan*/  kaweth_reset (struct kaweth_device*) ; 
 int /*<<< orphan*/  kaweth_resubmit_tl ; 
 int kaweth_set_receive_filter (struct kaweth_device*,int) ; 
 scalar_t__ kaweth_set_sofs_wait (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ kaweth_set_urb_size (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int kaweth_trigger_firmware (struct kaweth_device*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (void*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct kaweth_device*) ; 

__attribute__((used)) static int kaweth_probe(
		struct usb_interface *intf,
		const struct usb_device_id *id      /* from id_table */
	)
{
	struct device *dev = &intf->dev;
	struct usb_device *udev = interface_to_usbdev(intf);
	struct kaweth_device *kaweth;
	struct net_device *netdev;
	const eth_addr_t bcast_addr = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	int result = 0;
	int rv = -EIO;

	dev_dbg(dev,
		"Kawasaki Device Probe (Device number:%d): 0x%4.4x:0x%4.4x:0x%4.4x\n",
		udev->devnum, le16_to_cpu(udev->descriptor.idVendor),
		le16_to_cpu(udev->descriptor.idProduct),
		le16_to_cpu(udev->descriptor.bcdDevice));

	dev_dbg(dev, "Device at %p\n", udev);

	dev_dbg(dev, "Descriptor length: %x type: %x\n",
		(int)udev->descriptor.bLength,
		(int)udev->descriptor.bDescriptorType);

	netdev = alloc_etherdev(sizeof(*kaweth));
	if (!netdev)
		return -ENOMEM;

	kaweth = netdev_priv(netdev);
	kaweth->dev = udev;
	kaweth->net = netdev;
	kaweth->intf = intf;

	spin_lock_init(&kaweth->device_lock);
	init_waitqueue_head(&kaweth->term_wait);

	dev_dbg(dev, "Resetting.\n");

	kaweth_reset(kaweth);

	/*
	 * If high byte of bcdDevice is nonzero, firmware is already
	 * downloaded. Don't try to do it again, or we'll hang the device.
	 */

	if (le16_to_cpu(udev->descriptor.bcdDevice) >> 8) {
		dev_info(dev, "Firmware present in device.\n");
	} else {
		/* Download the firmware */
		dev_info(dev, "Downloading firmware...\n");
		kaweth->firmware_buf = (__u8 *)__get_free_page(GFP_KERNEL);
		if (!kaweth->firmware_buf) {
			rv = -ENOMEM;
			goto err_free_netdev;
		}
		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/new_code.bin",
						      100,
						      2)) < 0) {
			dev_err(dev, "Error downloading firmware (%d)\n",
				result);
			goto err_fw;
		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/new_code_fix.bin",
						      100,
						      3)) < 0) {
			dev_err(dev, "Error downloading firmware fix (%d)\n",
				result);
			goto err_fw;
		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/trigger_code.bin",
						      126,
						      2)) < 0) {
			dev_err(dev, "Error downloading trigger code (%d)\n",
				result);
			goto err_fw;

		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/trigger_code_fix.bin",
						      126,
						      3)) < 0) {
			dev_err(dev, "Error downloading trigger code fix (%d)\n", result);
			goto err_fw;
		}


		if ((result = kaweth_trigger_firmware(kaweth, 126)) < 0) {
			dev_err(dev, "Error triggering firmware (%d)\n", result);
			goto err_fw;
		}

		/* Device will now disappear for a moment...  */
		dev_info(dev, "Firmware loaded.  I'll be back...\n");
err_fw:
		free_page((unsigned long)kaweth->firmware_buf);
		free_netdev(netdev);
		return -EIO;
	}

	result = kaweth_read_configuration(kaweth);

	if(result < 0) {
		dev_err(dev, "Error reading configuration (%d), no net device created\n", result);
		goto err_free_netdev;
	}

	dev_info(dev, "Statistics collection: %x\n", kaweth->configuration.statistics_mask);
	dev_info(dev, "Multicast filter limit: %x\n", kaweth->configuration.max_multicast_filters & ((1 << 15) - 1));
	dev_info(dev, "MTU: %d\n", le16_to_cpu(kaweth->configuration.segment_size));
	dev_info(dev, "Read MAC address %pM\n", kaweth->configuration.hw_addr);

	if(!memcmp(&kaweth->configuration.hw_addr,
                   &bcast_addr,
		   sizeof(bcast_addr))) {
		dev_err(dev, "Firmware not functioning properly, no net device created\n");
		goto err_free_netdev;
	}

	if(kaweth_set_urb_size(kaweth, KAWETH_BUF_SIZE) < 0) {
		dev_dbg(dev, "Error setting URB size\n");
		goto err_free_netdev;
	}

	if(kaweth_set_sofs_wait(kaweth, KAWETH_SOFS_TO_WAIT) < 0) {
		dev_err(dev, "Error setting SOFS wait\n");
		goto err_free_netdev;
	}

	result = kaweth_set_receive_filter(kaweth,
                                           KAWETH_PACKET_FILTER_DIRECTED |
                                           KAWETH_PACKET_FILTER_BROADCAST |
                                           KAWETH_PACKET_FILTER_MULTICAST);

	if(result < 0) {
		dev_err(dev, "Error setting receive filter\n");
		goto err_free_netdev;
	}

	dev_dbg(dev, "Initializing net device.\n");

	kaweth->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->tx_urb)
		goto err_free_netdev;
	kaweth->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->rx_urb)
		goto err_only_tx;
	kaweth->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->irq_urb)
		goto err_tx_and_rx;

	kaweth->intbuffer = usb_alloc_coherent(	kaweth->dev,
						INTBUFFERSIZE,
						GFP_KERNEL,
						&kaweth->intbufferhandle);
	if (!kaweth->intbuffer)
		goto err_tx_and_rx_and_irq;
	kaweth->rx_buf = usb_alloc_coherent(	kaweth->dev,
						KAWETH_BUF_SIZE,
						GFP_KERNEL,
						&kaweth->rxbufferhandle);
	if (!kaweth->rx_buf)
		goto err_all_but_rxbuf;

	memcpy(netdev->broadcast, &bcast_addr, sizeof(bcast_addr));
	memcpy(netdev->dev_addr, &kaweth->configuration.hw_addr,
               sizeof(kaweth->configuration.hw_addr));

	netdev->netdev_ops = &kaweth_netdev_ops;
	netdev->watchdog_timeo = KAWETH_TX_TIMEOUT;
	netdev->mtu = le16_to_cpu(kaweth->configuration.segment_size);
	netdev->ethtool_ops = &ops;

	/* kaweth is zeroed as part of alloc_netdev */
	INIT_DELAYED_WORK(&kaweth->lowmem_work, kaweth_resubmit_tl);
	usb_set_intfdata(intf, kaweth);

	SET_NETDEV_DEV(netdev, dev);
	if (register_netdev(netdev) != 0) {
		dev_err(dev, "Error registering netdev.\n");
		goto err_intfdata;
	}

	dev_info(dev, "kaweth interface created at %s\n",
		 kaweth->net->name);

	return 0;

err_intfdata:
	usb_set_intfdata(intf, NULL);
	usb_free_coherent(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->rx_buf, kaweth->rxbufferhandle);
err_all_but_rxbuf:
	usb_free_coherent(kaweth->dev, INTBUFFERSIZE, (void *)kaweth->intbuffer, kaweth->intbufferhandle);
err_tx_and_rx_and_irq:
	usb_free_urb(kaweth->irq_urb);
err_tx_and_rx:
	usb_free_urb(kaweth->rx_urb);
err_only_tx:
	usb_free_urb(kaweth->tx_urb);
err_free_netdev:
	free_netdev(netdev);

	return rv;
}