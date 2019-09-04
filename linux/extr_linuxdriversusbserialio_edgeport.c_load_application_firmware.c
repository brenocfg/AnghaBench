#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ihex_binrec {int* data; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_5__ {int iDownloadFile; int FirmwareMajorVersion; int FirmwareMinorVersion; int /*<<< orphan*/  FirmwareBuildNumber; } ;
struct edgeport_serial {TYPE_4__* serial; TYPE_1__ product_info; } ;
struct device {int dummy; } ;
typedef  int __u32 ;
typedef  int __u16 ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
#define  EDGE_DOWNLOAD_FILE_80251 130 
#define  EDGE_DOWNLOAD_FILE_I930 129 
#define  EDGE_DOWNLOAD_FILE_NONE 128 
 int /*<<< orphan*/  USB_REQUEST_ION_EXEC_DL_CODE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_ihex_firmware (struct firmware const**,char const*,struct device*) ; 
 int sram_write (TYPE_4__*,int,int,int /*<<< orphan*/ ,int*) ; 
 int usb_control_msg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_application_firmware(struct edgeport_serial *edge_serial)
{
	struct device *dev = &edge_serial->serial->dev->dev;
	const struct ihex_binrec *rec;
	const struct firmware *fw;
	const char *fw_name;
	const char *fw_info;
	int response;
	__u32 Operaddr;
	__u16 build;

	switch (edge_serial->product_info.iDownloadFile) {
		case EDGE_DOWNLOAD_FILE_I930:
			fw_info = "downloading firmware version (930)";
			fw_name	= "edgeport/down.fw";
			break;

		case EDGE_DOWNLOAD_FILE_80251:
			fw_info = "downloading firmware version (80251)";
			fw_name	= "edgeport/down2.fw";
			break;

		case EDGE_DOWNLOAD_FILE_NONE:
			dev_dbg(dev, "No download file specified, skipping download\n");
			return;

		default:
			return;
	}

	response = request_ihex_firmware(&fw, fw_name,
				    &edge_serial->serial->dev->dev);
	if (response) {
		dev_err(dev, "Failed to load image \"%s\" err %d\n",
		       fw_name, response);
		return;
	}

	rec = (const struct ihex_binrec *)fw->data;
	build = (rec->data[2] << 8) | rec->data[3];

	dev_dbg(dev, "%s %d.%d.%d\n", fw_info, rec->data[0], rec->data[1], build);

	edge_serial->product_info.FirmwareMajorVersion = rec->data[0];
	edge_serial->product_info.FirmwareMinorVersion = rec->data[1];
	edge_serial->product_info.FirmwareBuildNumber = cpu_to_le16(build);

	for (rec = ihex_next_binrec(rec); rec;
	     rec = ihex_next_binrec(rec)) {
		Operaddr = be32_to_cpu(rec->addr);
		response = sram_write(edge_serial->serial,
				     Operaddr >> 16,
				     Operaddr & 0xFFFF,
				     be16_to_cpu(rec->len),
				     &rec->data[0]);
		if (response < 0) {
			dev_err(&edge_serial->serial->dev->dev,
				"sram_write failed (%x, %x, %d)\n",
				Operaddr >> 16, Operaddr & 0xFFFF,
				be16_to_cpu(rec->len));
			break;
		}
	}

	dev_dbg(dev, "sending exec_dl_code\n");
	response = usb_control_msg (edge_serial->serial->dev,
				    usb_sndctrlpipe(edge_serial->serial->dev, 0),
				    USB_REQUEST_ION_EXEC_DL_CODE,
				    0x40, 0x4000, 0x0001, NULL, 0, 3000);

	release_firmware(fw);
}