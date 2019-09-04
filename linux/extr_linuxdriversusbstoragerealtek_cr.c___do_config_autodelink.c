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
typedef  int u8 ;
typedef  int u16 ;
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int rts51x_bulk_transport_special (struct us_data*,int /*<<< orphan*/ ,int*,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int) ; 

__attribute__((used)) static int __do_config_autodelink(struct us_data *us, u8 *data, u16 len)
{
	int retval;
	u8 cmnd[12] = {0};
	u8 *buf;

	usb_stor_dbg(us, "addr = 0xfe47, len = %d\n", len);

	buf = kmemdup(data, len, GFP_NOIO);
	if (!buf)
		return USB_STOR_TRANSPORT_ERROR;

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0E;
	cmnd[2] = 0xfe;
	cmnd[3] = 0x47;
	cmnd[4] = (u8)(len >> 8);
	cmnd[5] = (u8)len;

	retval = rts51x_bulk_transport_special(us, 0, cmnd, 12, buf, len, DMA_TO_DEVICE, NULL);
	kfree(buf);
	if (retval != USB_STOR_TRANSPORT_GOOD) {
		return -EIO;
	}

	return 0;
}