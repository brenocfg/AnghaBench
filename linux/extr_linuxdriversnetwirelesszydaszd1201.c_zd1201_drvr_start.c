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
struct zd1201 {int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  endp_in; int /*<<< orphan*/  usb; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ZD1201_CMDCODE_ALLOC ; 
 int /*<<< orphan*/  ZD1201_CMDCODE_INIT ; 
 int /*<<< orphan*/  ZD1201_RID_CNFMAXTXBUFFERNUMBER ; 
 int /*<<< orphan*/  ZD1201_RXSIZE ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zd1201*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zd1201_docmd (struct zd1201*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zd1201_getconfig (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zd1201_usbrx ; 

__attribute__((used)) static int zd1201_drvr_start(struct zd1201 *zd)
{
	int err, i;
	short max;
	__le16 zdmax;
	unsigned char *buffer;

	buffer = kzalloc(ZD1201_RXSIZE, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	usb_fill_bulk_urb(zd->rx_urb, zd->usb, 
	    usb_rcvbulkpipe(zd->usb, zd->endp_in), buffer, ZD1201_RXSIZE,
	    zd1201_usbrx, zd);

	err = usb_submit_urb(zd->rx_urb, GFP_KERNEL);
	if (err)
		goto err_buffer;

	err = zd1201_docmd(zd, ZD1201_CMDCODE_INIT, 0, 0, 0);
	if (err)
		goto err_urb;

	err = zd1201_getconfig(zd, ZD1201_RID_CNFMAXTXBUFFERNUMBER, &zdmax,
	    sizeof(__le16));
	if (err)
		goto err_urb;

	max = le16_to_cpu(zdmax);
	for (i=0; i<max; i++) {
		err = zd1201_docmd(zd, ZD1201_CMDCODE_ALLOC, 1514, 0, 0);
		if (err)
			goto err_urb;
	}

	return 0;

err_urb:
	usb_kill_urb(zd->rx_urb);
	return err;
err_buffer:
	kfree(buffer);
	return err;
}