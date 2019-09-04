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
struct uea_softc {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_TIMEOUT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_IDMA_PIPE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,...) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_idma_write(struct uea_softc *sc, const void *data, u32 size)
{
	int ret = -ENOMEM;
	u8 *xfer_buff;
	int bytes_read;

	xfer_buff = kmemdup(data, size, GFP_KERNEL);
	if (!xfer_buff) {
		uea_err(INS_TO_USBDEV(sc), "can't allocate xfer_buff\n");
		return ret;
	}

	ret = usb_bulk_msg(sc->usb_dev,
			 usb_sndbulkpipe(sc->usb_dev, UEA_IDMA_PIPE),
			 xfer_buff, size, &bytes_read, BULK_TIMEOUT);

	kfree(xfer_buff);
	if (ret < 0)
		return ret;
	if (size != bytes_read) {
		uea_err(INS_TO_USBDEV(sc), "size != bytes_read %d %d\n", size,
		       bytes_read);
		return -EIO;
	}

	return 0;
}