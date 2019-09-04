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
struct wl1271 {int /*<<< orphan*/ * fw; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int EINVAL ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int wl1271_boot_upload_firmware_chunk (struct wl1271*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wl1271_info (char*,int) ; 

int wlcore_boot_upload_firmware(struct wl1271 *wl)
{
	u32 chunks, addr, len;
	int ret = 0;
	u8 *fw;

	fw = wl->fw;
	chunks = be32_to_cpup((__be32 *) fw);
	fw += sizeof(u32);

	wl1271_debug(DEBUG_BOOT, "firmware chunks to be uploaded: %u", chunks);

	while (chunks--) {
		addr = be32_to_cpup((__be32 *) fw);
		fw += sizeof(u32);
		len = be32_to_cpup((__be32 *) fw);
		fw += sizeof(u32);

		if (len > 300000) {
			wl1271_info("firmware chunk too long: %u", len);
			return -EINVAL;
		}
		wl1271_debug(DEBUG_BOOT, "chunk %d addr 0x%x len %u",
			     chunks, addr, len);
		ret = wl1271_boot_upload_firmware_chunk(wl, fw, len, addr);
		if (ret != 0)
			break;
		fw += len;
	}

	return ret;
}