#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct hso_net {void* mux_bulk_tx_buf; void* mux_bulk_tx_urb; void** mux_bulk_rx_buf_pool; void** mux_bulk_rx_urb_pool; void* out_endp; void* in_endp; struct hso_device* parent; struct net_device* net; } ;
struct TYPE_2__ {struct hso_net* dev_net; } ;
struct hso_device {TYPE_1__ port_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MUX_BULK_RX_BUF_COUNT ; 
 int /*<<< orphan*/  MUX_BULK_RX_BUF_SIZE ; 
 int /*<<< orphan*/  MUX_BULK_TX_BUF_SIZE ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  add_net_device (struct hso_device*) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hso_device* hso_create_device (struct usb_interface*,int) ; 
 int /*<<< orphan*/  hso_create_rfkill (struct hso_device*,struct usb_interface*) ; 
 int /*<<< orphan*/  hso_free_net_device (struct hso_device*) ; 
 void* hso_get_ep (struct usb_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_log_port (struct hso_device*) ; 
 int /*<<< orphan*/  hso_net_init ; 
 int /*<<< orphan*/  hso_type ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hso_net* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hso_device *hso_create_net_device(struct usb_interface *interface,
						int port_spec)
{
	int result, i;
	struct net_device *net;
	struct hso_net *hso_net;
	struct hso_device *hso_dev;

	hso_dev = hso_create_device(interface, port_spec);
	if (!hso_dev)
		return NULL;

	/* allocate our network device, then we can put in our private data */
	/* call hso_net_init to do the basic initialization */
	net = alloc_netdev(sizeof(struct hso_net), "hso%d", NET_NAME_UNKNOWN,
			   hso_net_init);
	if (!net) {
		dev_err(&interface->dev, "Unable to create ethernet device\n");
		goto exit;
	}

	hso_net = netdev_priv(net);

	hso_dev->port_data.dev_net = hso_net;
	hso_net->net = net;
	hso_net->parent = hso_dev;

	hso_net->in_endp = hso_get_ep(interface, USB_ENDPOINT_XFER_BULK,
				      USB_DIR_IN);
	if (!hso_net->in_endp) {
		dev_err(&interface->dev, "Can't find BULK IN endpoint\n");
		goto exit;
	}
	hso_net->out_endp = hso_get_ep(interface, USB_ENDPOINT_XFER_BULK,
				       USB_DIR_OUT);
	if (!hso_net->out_endp) {
		dev_err(&interface->dev, "Can't find BULK OUT endpoint\n");
		goto exit;
	}
	SET_NETDEV_DEV(net, &interface->dev);
	SET_NETDEV_DEVTYPE(net, &hso_type);

	/* start allocating */
	for (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) {
		hso_net->mux_bulk_rx_urb_pool[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!hso_net->mux_bulk_rx_urb_pool[i])
			goto exit;
		hso_net->mux_bulk_rx_buf_pool[i] = kzalloc(MUX_BULK_RX_BUF_SIZE,
							   GFP_KERNEL);
		if (!hso_net->mux_bulk_rx_buf_pool[i])
			goto exit;
	}
	hso_net->mux_bulk_tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!hso_net->mux_bulk_tx_urb)
		goto exit;
	hso_net->mux_bulk_tx_buf = kzalloc(MUX_BULK_TX_BUF_SIZE, GFP_KERNEL);
	if (!hso_net->mux_bulk_tx_buf)
		goto exit;

	add_net_device(hso_dev);

	/* registering our net device */
	result = register_netdev(net);
	if (result) {
		dev_err(&interface->dev, "Failed to register device\n");
		goto exit;
	}

	hso_log_port(hso_dev);

	hso_create_rfkill(hso_dev, interface);

	return hso_dev;
exit:
	hso_free_net_device(hso_dev);
	return NULL;
}