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
typedef  scalar_t__ u32 ;
struct mt76x0_dma_buf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {TYPE_2__ mt76; } ;
struct TYPE_3__ {int /*<<< orphan*/  dlm_len; int /*<<< orphan*/  ilm_len; } ;
struct mt76_fw {scalar_t__ ilm; TYPE_1__ hdr; int /*<<< orphan*/  ivb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_FW_URB_SIZE ; 
 int MT_MCU_DLM_OFFSET ; 
 int /*<<< orphan*/  MT_VEND_DEV_MODE ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  firmware_running (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mt76x0_dma_fw (struct mt76x0_dev*,struct mt76x0_dma_buf*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ mt76x0_usb_alloc_buf (struct mt76x0_dev*,int /*<<< orphan*/ ,struct mt76x0_dma_buf*) ; 
 int /*<<< orphan*/  mt76x0_usb_free_buf (struct mt76x0_dev*,struct mt76x0_dma_buf*) ; 
 int mt76x0_vendor_request (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int
mt76x0_upload_firmware(struct mt76x0_dev *dev, const struct mt76_fw *fw)
{
	struct mt76x0_dma_buf dma_buf;
	void *ivb;
	u32 ilm_len, dlm_len;
	int i, ret;

	ivb = kmemdup(fw->ivb, sizeof(fw->ivb), GFP_KERNEL);
	if (!ivb)
		return -ENOMEM;
	if (mt76x0_usb_alloc_buf(dev, MCU_FW_URB_SIZE, &dma_buf)) {
		ret = -ENOMEM;
		goto error;
	}

	ilm_len = le32_to_cpu(fw->hdr.ilm_len) - sizeof(fw->ivb);
	dev_dbg(dev->mt76.dev, "loading FW - ILM %u + IVB %zu\n",
		ilm_len, sizeof(fw->ivb));
	ret = mt76x0_dma_fw(dev, &dma_buf, fw->ilm, ilm_len, sizeof(fw->ivb));
	if (ret)
		goto error;

	dlm_len = le32_to_cpu(fw->hdr.dlm_len);
	dev_dbg(dev->mt76.dev, "loading FW - DLM %u\n", dlm_len);
	ret = mt76x0_dma_fw(dev, &dma_buf, fw->ilm + ilm_len,
			     dlm_len, MT_MCU_DLM_OFFSET);
	if (ret)
		goto error;

	ret = mt76x0_vendor_request(dev, MT_VEND_DEV_MODE, USB_DIR_OUT,
				     0x12, 0, ivb, sizeof(fw->ivb));
	if (ret < 0)
		goto error;
	ret = 0;

	for (i = 100; i && !firmware_running(dev); i--)
		msleep(10);
	if (!i) {
		ret = -ETIMEDOUT;
		goto error;
	}

	dev_dbg(dev->mt76.dev, "Firmware running!\n");
error:
	kfree(ivb);
	mt76x0_usb_free_buf(dev, &dma_buf);

	return ret;
}