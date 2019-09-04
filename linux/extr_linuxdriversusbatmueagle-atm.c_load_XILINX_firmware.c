#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct uea_softc {TYPE_1__* usb_dev; } ;
struct firmware {int size; scalar_t__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EILSEQ ; 
 char* FPGA930_FIRMWARE ; 
 TYPE_1__* INS_TO_USBDEV (struct uea_softc*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_enters (TYPE_1__*) ; 
 int /*<<< orphan*/  uea_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  uea_leaves (TYPE_1__*) ; 
 int uea_request (struct uea_softc*,int,int,int,scalar_t__ const*) ; 
 int uea_send_modem_cmd (TYPE_1__*,int,int,scalar_t__*) ; 

__attribute__((used)) static int load_XILINX_firmware(struct uea_softc *sc)
{
	const struct firmware *fw_entry;
	int ret, size, u, ln;
	const u8 *pfw;
	u8 value;
	char *fw_name = FPGA930_FIRMWARE;

	uea_enters(INS_TO_USBDEV(sc));

	ret = request_firmware(&fw_entry, fw_name, &sc->usb_dev->dev);
	if (ret) {
		uea_err(INS_TO_USBDEV(sc), "firmware %s is not available\n",
		       fw_name);
		goto err0;
	}

	pfw = fw_entry->data;
	size = fw_entry->size;
	if (size != 0x577B) {
		uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n",
		       fw_name);
		ret = -EILSEQ;
		goto err1;
	}
	for (u = 0; u < size; u += ln) {
		ln = min(size - u, 64);
		ret = uea_request(sc, 0xe, 0, ln, pfw + u);
		if (ret < 0) {
			uea_err(INS_TO_USBDEV(sc),
			       "elsa download data failed (%d)\n", ret);
			goto err1;
		}
	}

	/* finish to send the fpga */
	ret = uea_request(sc, 0xe, 1, 0, NULL);
	if (ret < 0) {
		uea_err(INS_TO_USBDEV(sc),
				"elsa download data failed (%d)\n", ret);
		goto err1;
	}

	/* Tell the modem we finish : de-assert reset */
	value = 0;
	ret = uea_send_modem_cmd(sc->usb_dev, 0xe, 1, &value);
	if (ret < 0)
		uea_err(sc->usb_dev, "elsa de-assert failed with error"
								" %d\n", ret);

err1:
	release_firmware(fw_entry);
err0:
	uea_leaves(INS_TO_USBDEV(sc));
	return ret;
}