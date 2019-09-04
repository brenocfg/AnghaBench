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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_interface {int quirks; int /*<<< orphan*/  interface_id; int /*<<< orphan*/  dev; struct gb_host_device* hd; } ;
struct gb_host_device {int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_SELECTOR_INDEX_NULL ; 
 int /*<<< orphan*/  DME_TOSHIBA_GMP_INIT_STATUS ; 
 int /*<<< orphan*/  DME_T_TST_SRC_INCREMENT ; 
 int ENODEV ; 
#define  GB_INIT_BOOTROM_FALLBACK_UNIPRO_BOOT_STARTED 130 
#define  GB_INIT_BOOTROM_UNIPRO_BOOT_STARTED 129 
#define  GB_INIT_S2_LOADER_BOOT_STARTED 128 
 unsigned long GB_INTERFACE_QUIRK_FORCED_DISABLE ; 
 unsigned long GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH ; 
 unsigned long GB_INTERFACE_QUIRK_NO_BUNDLE_ACTIVATE ; 
 unsigned long GB_INTERFACE_QUIRK_NO_CPORT_FEATURES ; 
 int GB_INTERFACE_QUIRK_NO_INIT_STATUS ; 
 unsigned long GB_INTERFACE_QUIRK_NO_PM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_svc_dme_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int gb_svc_dme_peer_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_interface_read_and_clear_init_status(struct gb_interface *intf)
{
	struct gb_host_device *hd = intf->hd;
	unsigned long bootrom_quirks;
	unsigned long s2l_quirks;
	int ret;
	u32 value;
	u16 attr;
	u8 init_status;

	/*
	 * ES2 bridges use T_TstSrcIncrement for the init status.
	 *
	 * FIXME: Remove ES2 support
	 */
	if (intf->quirks & GB_INTERFACE_QUIRK_NO_INIT_STATUS)
		attr = DME_T_TST_SRC_INCREMENT;
	else
		attr = DME_TOSHIBA_GMP_INIT_STATUS;

	ret = gb_svc_dme_peer_get(hd->svc, intf->interface_id, attr,
				  DME_SELECTOR_INDEX_NULL, &value);
	if (ret)
		return ret;

	/*
	 * A nonzero init status indicates the module has finished
	 * initializing.
	 */
	if (!value) {
		dev_err(&intf->dev, "invalid init status\n");
		return -ENODEV;
	}

	/*
	 * Extract the init status.
	 *
	 * For ES2: We need to check lowest 8 bits of 'value'.
	 * For ES3: We need to check highest 8 bits out of 32 of 'value'.
	 *
	 * FIXME: Remove ES2 support
	 */
	if (intf->quirks & GB_INTERFACE_QUIRK_NO_INIT_STATUS)
		init_status = value & 0xff;
	else
		init_status = value >> 24;

	/*
	 * Check if the interface is executing the quirky ES3 bootrom that,
	 * for example, requires E2EFC, CSD and CSV to be disabled.
	 */
	bootrom_quirks = GB_INTERFACE_QUIRK_NO_CPORT_FEATURES |
				GB_INTERFACE_QUIRK_FORCED_DISABLE |
				GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH |
				GB_INTERFACE_QUIRK_NO_BUNDLE_ACTIVATE;

	s2l_quirks = GB_INTERFACE_QUIRK_NO_PM;

	switch (init_status) {
	case GB_INIT_BOOTROM_UNIPRO_BOOT_STARTED:
	case GB_INIT_BOOTROM_FALLBACK_UNIPRO_BOOT_STARTED:
		intf->quirks |= bootrom_quirks;
		break;
	case GB_INIT_S2_LOADER_BOOT_STARTED:
		/* S2 Loader doesn't support runtime PM */
		intf->quirks &= ~bootrom_quirks;
		intf->quirks |= s2l_quirks;
		break;
	default:
		intf->quirks &= ~bootrom_quirks;
		intf->quirks &= ~s2l_quirks;
	}

	/* Clear the init status. */
	return gb_svc_dme_peer_set(hd->svc, intf->interface_id, attr,
				   DME_SELECTOR_INDEX_NULL, 0);
}