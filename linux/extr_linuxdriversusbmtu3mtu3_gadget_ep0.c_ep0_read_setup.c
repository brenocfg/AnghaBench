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
typedef  int u32 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct mtu3_request {int /*<<< orphan*/  request; } ;
struct mtu3 {int /*<<< orphan*/  ep0_state; int /*<<< orphan*/  mac_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int EP0_DPHTX ; 
 int EP0_SETUPPKTRDY ; 
 int EP0_W1C_BITS ; 
 int /*<<< orphan*/  MU3D_EP0_STATE_RX ; 
 int /*<<< orphan*/  MU3D_EP0_STATE_TX ; 
 int /*<<< orphan*/  U3D_EP0CSR ; 
 int /*<<< orphan*/  U3D_RXCOUNT0 ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ep0_read_fifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ep0_req_giveback (struct mtu3*,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mtu3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtu3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtu3_request* next_ep0_request (struct mtu3*) ; 

__attribute__((used)) static void ep0_read_setup(struct mtu3 *mtu, struct usb_ctrlrequest *setup)
{
	struct mtu3_request *mreq;
	u32 count;
	u32 csr;

	csr = mtu3_readl(mtu->mac_base, U3D_EP0CSR) & EP0_W1C_BITS;
	count = mtu3_readl(mtu->mac_base, U3D_RXCOUNT0);

	ep0_read_fifo(mtu->ep0, (u8 *)setup, count);

	dev_dbg(mtu->dev, "SETUP req%02x.%02x v%04x i%04x l%04x\n",
		 setup->bRequestType, setup->bRequest,
		 le16_to_cpu(setup->wValue), le16_to_cpu(setup->wIndex),
		 le16_to_cpu(setup->wLength));

	/* clean up any leftover transfers */
	mreq = next_ep0_request(mtu);
	if (mreq)
		ep0_req_giveback(mtu, &mreq->request);

	if (le16_to_cpu(setup->wLength) == 0) {
		;	/* no data stage, nothing to do */
	} else if (setup->bRequestType & USB_DIR_IN) {
		mtu3_writel(mtu->mac_base, U3D_EP0CSR,
			csr | EP0_SETUPPKTRDY | EP0_DPHTX);
		mtu->ep0_state = MU3D_EP0_STATE_TX;
	} else {
		mtu3_writel(mtu->mac_base, U3D_EP0CSR,
			(csr | EP0_SETUPPKTRDY) & (~EP0_DPHTX));
		mtu->ep0_state = MU3D_EP0_STATE_RX;
	}
}