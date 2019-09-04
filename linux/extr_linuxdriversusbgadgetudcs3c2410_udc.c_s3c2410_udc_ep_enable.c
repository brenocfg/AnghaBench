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
typedef  int u32 ;
struct usb_ep {scalar_t__ name; int maxpacket; } ;
struct usb_endpoint_descriptor {scalar_t__ bDescriptorType; int bEndpointAddress; } ;
struct TYPE_3__ {scalar_t__ speed; } ;
struct s3c2410_udc {TYPE_1__ gadget; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor const* desc; } ;
struct s3c2410_ep {int bEndpointAddress; int num; scalar_t__ halted; TYPE_2__ ep; struct s3c2410_udc* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NORMAL ; 
 int EINVAL ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  S3C2410_UDC_EP_INT_EN_REG ; 
 int S3C2410_UDC_ICSR1_CLRDT ; 
 int S3C2410_UDC_ICSR1_FFLUSH ; 
 int S3C2410_UDC_ICSR2_DMAIEN ; 
 int S3C2410_UDC_ICSR2_MODEIN ; 
 int /*<<< orphan*/  S3C2410_UDC_INDEX_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_IN_CSR1_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_IN_CSR2_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_MAXP_REG ; 
 int S3C2410_UDC_OCSR1_CLRDT ; 
 int S3C2410_UDC_OCSR1_FFLUSH ; 
 int S3C2410_UDC_OCSR2_DMAIEN ; 
 int /*<<< orphan*/  S3C2410_UDC_OUT_CSR1_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_OUT_CSR2_REG ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_DT_ENDPOINT ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,scalar_t__,int,int,char*,int) ; 
 scalar_t__ ep0name ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  s3c2410_udc_set_halt (struct usb_ep*,int /*<<< orphan*/ ) ; 
 struct s3c2410_ep* to_s3c2410_ep (struct usb_ep*) ; 
 int udc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write (int,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int s3c2410_udc_ep_enable(struct usb_ep *_ep,
				 const struct usb_endpoint_descriptor *desc)
{
	struct s3c2410_udc	*dev;
	struct s3c2410_ep	*ep;
	u32			max, tmp;
	unsigned long		flags;
	u32			csr1, csr2;
	u32			int_en_reg;

	ep = to_s3c2410_ep(_ep);

	if (!_ep || !desc
			|| _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		return -EINVAL;

	dev = ep->dev;
	if (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		return -ESHUTDOWN;

	max = usb_endpoint_maxp(desc);

	local_irq_save(flags);
	_ep->maxpacket = max;
	ep->ep.desc = desc;
	ep->halted = 0;
	ep->bEndpointAddress = desc->bEndpointAddress;

	/* set max packet */
	udc_write(ep->num, S3C2410_UDC_INDEX_REG);
	udc_write(max >> 3, S3C2410_UDC_MAXP_REG);

	/* set type, direction, address; reset fifo counters */
	if (desc->bEndpointAddress & USB_DIR_IN) {
		csr1 = S3C2410_UDC_ICSR1_FFLUSH|S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_MODEIN|S3C2410_UDC_ICSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_IN_CSR2_REG);
	} else {
		/* don't flush in fifo or it will cause endpoint interrupt */
		csr1 = S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_IN_CSR2_REG);

		csr1 = S3C2410_UDC_OCSR1_FFLUSH | S3C2410_UDC_OCSR1_CLRDT;
		csr2 = S3C2410_UDC_OCSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_OUT_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_OUT_CSR2_REG);
	}

	/* enable irqs */
	int_en_reg = udc_read(S3C2410_UDC_EP_INT_EN_REG);
	udc_write(int_en_reg | (1 << ep->num), S3C2410_UDC_EP_INT_EN_REG);

	/* print some debug message */
	tmp = desc->bEndpointAddress;
	dprintk(DEBUG_NORMAL, "enable %s(%d) ep%x%s-blk max %02x\n",
		 _ep->name, ep->num, tmp,
		 desc->bEndpointAddress & USB_DIR_IN ? "in" : "out", max);

	local_irq_restore(flags);
	s3c2410_udc_set_halt(_ep, 0);

	return 0;
}