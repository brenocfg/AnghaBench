#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct wiphy {int /*<<< orphan*/  hw_version; int /*<<< orphan*/  fw_version; } ;
struct TYPE_16__ {TYPE_4__* data; } ;
struct TYPE_14__ {TYPE_2__* data; } ;
struct TYPE_18__ {int rev; int patch; scalar_t__ hdr_format; int opensource; scalar_t__ pcm_request_failed; TYPE_5__ pcm; TYPE_3__ ucode; } ;
struct b43_wldev {int qos_enabled; int hwcrypto_enabled; TYPE_8__* wl; TYPE_7__ fw; TYPE_1__* dev; } ;
struct b43_fw_header {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_19__ {TYPE_6__* hw; } ;
struct TYPE_17__ {int queues; struct wiphy* wiphy; } ;
struct TYPE_15__ {size_t const size; scalar_t__ data; } ;
struct TYPE_13__ {size_t const size; scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  core_id; } ;

/* Variables and functions */
 int B43_FWCAPA_HWCRYPTO ; 
 int B43_FWCAPA_QOS ; 
 scalar_t__ B43_FW_HDR_351 ; 
 scalar_t__ B43_FW_HDR_410 ; 
 scalar_t__ B43_FW_HDR_598 ; 
 int B43_IRQ_ALL ; 
 scalar_t__ B43_IRQ_MAC_SUSPENDED ; 
 scalar_t__ B43_MACCTL_PSM_JMP0 ; 
 scalar_t__ B43_MACCTL_PSM_RUN ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_REASON ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_MMIO_SHM_DATA ; 
 int B43_SHM_AUTOINC_W ; 
 int B43_SHM_HW ; 
 int /*<<< orphan*/  B43_SHM_SCRATCH ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_UCODEDATE ; 
 int /*<<< orphan*/  B43_SHM_SH_UCODEPATCH ; 
 int /*<<< orphan*/  B43_SHM_SH_UCODEREV ; 
 int /*<<< orphan*/  B43_SHM_SH_UCODETIME ; 
 int B43_SHM_UCODE ; 
 int /*<<< orphan*/  B43_WARN_ON (scalar_t__) ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int b43_fwcapa_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  b43_print_fw_helptext (TYPE_8__*,int) ; 
 scalar_t__ b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_control_word (struct b43_wldev*,int,int) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43err (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  b43info (TYPE_8__*,char*,...) ; 
 int /*<<< orphan*/  b43warn (TYPE_8__*,char*) ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int b43_upload_microcode(struct b43_wldev *dev)
{
	struct wiphy *wiphy = dev->wl->hw->wiphy;
	const size_t hdr_len = sizeof(struct b43_fw_header);
	const __be32 *data;
	unsigned int i, len;
	u16 fwrev, fwpatch, fwdate, fwtime;
	u32 tmp, macctl;
	int err = 0;

	/* Jump the microcode PSM to offset 0 */
	macctl = b43_read32(dev, B43_MMIO_MACCTL);
	B43_WARN_ON(macctl & B43_MACCTL_PSM_RUN);
	macctl |= B43_MACCTL_PSM_JMP0;
	b43_write32(dev, B43_MMIO_MACCTL, macctl);
	/* Zero out all microcode PSM registers and shared memory. */
	for (i = 0; i < 64; i++)
		b43_shm_write16(dev, B43_SHM_SCRATCH, i, 0);
	for (i = 0; i < 4096; i += 2)
		b43_shm_write16(dev, B43_SHM_SHARED, i, 0);

	/* Upload Microcode. */
	data = (__be32 *) (dev->fw.ucode.data->data + hdr_len);
	len = (dev->fw.ucode.data->size - hdr_len) / sizeof(__be32);
	b43_shm_control_word(dev, B43_SHM_UCODE | B43_SHM_AUTOINC_W, 0x0000);
	for (i = 0; i < len; i++) {
		b43_write32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
		udelay(10);
	}

	if (dev->fw.pcm.data) {
		/* Upload PCM data. */
		data = (__be32 *) (dev->fw.pcm.data->data + hdr_len);
		len = (dev->fw.pcm.data->size - hdr_len) / sizeof(__be32);
		b43_shm_control_word(dev, B43_SHM_HW, 0x01EA);
		b43_write32(dev, B43_MMIO_SHM_DATA, 0x00004000);
		/* No need for autoinc bit in SHM_HW */
		b43_shm_control_word(dev, B43_SHM_HW, 0x01EB);
		for (i = 0; i < len; i++) {
			b43_write32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
			udelay(10);
		}
	}

	b43_write32(dev, B43_MMIO_GEN_IRQ_REASON, B43_IRQ_ALL);

	/* Start the microcode PSM */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_JMP0,
		      B43_MACCTL_PSM_RUN);

	/* Wait for the microcode to load and respond */
	i = 0;
	while (1) {
		tmp = b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);
		if (tmp == B43_IRQ_MAC_SUSPENDED)
			break;
		i++;
		if (i >= 20) {
			b43err(dev->wl, "Microcode not responding\n");
			b43_print_fw_helptext(dev->wl, 1);
			err = -ENODEV;
			goto error;
		}
		msleep(50);
	}
	b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);	/* dummy read */

	/* Get and check the revisions. */
	fwrev = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEREV);
	fwpatch = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEPATCH);
	fwdate = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEDATE);
	fwtime = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODETIME);

	if (fwrev <= 0x128) {
		b43err(dev->wl, "YOUR FIRMWARE IS TOO OLD. Firmware from "
		       "binary drivers older than version 4.x is unsupported. "
		       "You must upgrade your firmware files.\n");
		b43_print_fw_helptext(dev->wl, 1);
		err = -EOPNOTSUPP;
		goto error;
	}
	dev->fw.rev = fwrev;
	dev->fw.patch = fwpatch;
	if (dev->fw.rev >= 598)
		dev->fw.hdr_format = B43_FW_HDR_598;
	else if (dev->fw.rev >= 410)
		dev->fw.hdr_format = B43_FW_HDR_410;
	else
		dev->fw.hdr_format = B43_FW_HDR_351;
	WARN_ON(dev->fw.opensource != (fwdate == 0xFFFF));

	dev->qos_enabled = dev->wl->hw->queues > 1;
	/* Default to firmware/hardware crypto acceleration. */
	dev->hwcrypto_enabled = true;

	if (dev->fw.opensource) {
		u16 fwcapa;

		/* Patchlevel info is encoded in the "time" field. */
		dev->fw.patch = fwtime;
		b43info(dev->wl, "Loading OpenSource firmware version %u.%u\n",
			dev->fw.rev, dev->fw.patch);

		fwcapa = b43_fwcapa_read(dev);
		if (!(fwcapa & B43_FWCAPA_HWCRYPTO) || dev->fw.pcm_request_failed) {
			b43info(dev->wl, "Hardware crypto acceleration not supported by firmware\n");
			/* Disable hardware crypto and fall back to software crypto. */
			dev->hwcrypto_enabled = false;
		}
		/* adding QoS support should use an offline discovery mechanism */
		WARN(fwcapa & B43_FWCAPA_QOS, "QoS in OpenFW not supported\n");
	} else {
		b43info(dev->wl, "Loading firmware version %u.%u "
			"(20%.2i-%.2i-%.2i %.2i:%.2i:%.2i)\n",
			fwrev, fwpatch,
			(fwdate >> 12) & 0xF, (fwdate >> 8) & 0xF, fwdate & 0xFF,
			(fwtime >> 11) & 0x1F, (fwtime >> 5) & 0x3F, fwtime & 0x1F);
		if (dev->fw.pcm_request_failed) {
			b43warn(dev->wl, "No \"pcm5.fw\" firmware file found. "
				"Hardware accelerated cryptography is disabled.\n");
			b43_print_fw_helptext(dev->wl, 0);
		}
	}

	snprintf(wiphy->fw_version, sizeof(wiphy->fw_version), "%u.%u",
			dev->fw.rev, dev->fw.patch);
	wiphy->hw_version = dev->dev->core_id;

	if (dev->fw.hdr_format == B43_FW_HDR_351) {
		/* We're over the deadline, but we keep support for old fw
		 * until it turns out to be in major conflict with something new. */
		b43warn(dev->wl, "You are using an old firmware image. "
			"Support for old firmware will be removed soon "
			"(official deadline was July 2008).\n");
		b43_print_fw_helptext(dev->wl, 0);
	}

	return 0;

error:
	/* Stop the microcode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_RUN,
		      B43_MACCTL_PSM_JMP0);

	return err;
}