#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_tx_data_port {TYPE_3__* tx_data_list; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {scalar_t__ urb; } ;
struct TYPE_5__ {scalar_t__ urb; } ;
struct usb_card_rec {TYPE_4__ tx_cmd; struct usb_tx_data_port* port; TYPE_2__* rx_data_list; int /*<<< orphan*/  rx_data_urb_pending; TYPE_1__ rx_cmd; int /*<<< orphan*/  rx_cmd_urb_pending; struct mwifiex_adapter* adapter; int /*<<< orphan*/  fw_done; } ;
struct mwifiex_adapter {int /*<<< orphan*/  work_flags; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_7__ {scalar_t__ urb; } ;
struct TYPE_6__ {scalar_t__ urb; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_ENABLING ; 
 int /*<<< orphan*/  MWIFIEX_IS_SUSPENDED ; 
 int MWIFIEX_RX_DATA_URB ; 
 int MWIFIEX_TX_DATA_PORT ; 
 int MWIFIEX_TX_DATA_URB ; 
 int /*<<< orphan*/  WARN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_enable_hs (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct usb_card_rec* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_usb_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usb_card_rec *card = usb_get_intfdata(intf);
	struct mwifiex_adapter *adapter;
	struct usb_tx_data_port *port;
	int i, j;

	/* Might still be loading firmware */
	wait_for_completion(&card->fw_done);

	adapter = card->adapter;
	if (!adapter) {
		dev_err(&intf->dev, "card is not valid\n");
		return 0;
	}

	if (unlikely(test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)))
		mwifiex_dbg(adapter, WARN,
			    "Device already suspended\n");

	/* Enable the Host Sleep */
	if (!mwifiex_enable_hs(adapter)) {
		mwifiex_dbg(adapter, ERROR,
			    "cmd: failed to suspend\n");
		clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
		return -EFAULT;
	}


	/* 'MWIFIEX_IS_SUSPENDED' bit indicates device is suspended.
	 * It must be set here before the usb_kill_urb() calls. Reason
	 * is in the complete handlers, urb->status(= -ENOENT) and
	 * this flag is used in combination to distinguish between a
	 * 'suspended' state and a 'disconnect' one.
	 */
	set_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);

	if (atomic_read(&card->rx_cmd_urb_pending) && card->rx_cmd.urb)
		usb_kill_urb(card->rx_cmd.urb);

	if (atomic_read(&card->rx_data_urb_pending))
		for (i = 0; i < MWIFIEX_RX_DATA_URB; i++)
			if (card->rx_data_list[i].urb)
				usb_kill_urb(card->rx_data_list[i].urb);

	for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) {
		port = &card->port[i];
		for (j = 0; j < MWIFIEX_TX_DATA_URB; j++) {
			if (port->tx_data_list[j].urb)
				usb_kill_urb(port->tx_data_list[j].urb);
		}
	}

	if (card->tx_cmd.urb)
		usb_kill_urb(card->tx_cmd.urb);

	return 0;
}