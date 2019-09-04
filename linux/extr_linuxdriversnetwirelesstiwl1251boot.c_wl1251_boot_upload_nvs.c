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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct wl1251 {size_t* nvs; size_t nvs_len; int fw_len; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int ENODEV ; 
 int /*<<< orphan*/  WL1251_PART_DOWN_MEM_SIZE ; 
 int /*<<< orphan*/  WL1251_PART_DOWN_REG_SIZE ; 
 int /*<<< orphan*/  WL1251_PART_DOWN_REG_START ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  wl1251_mem_write32 (struct wl1251*,int,size_t) ; 
 int /*<<< orphan*/  wl1251_set_partition (struct wl1251*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_boot_upload_nvs(struct wl1251 *wl)
{
	size_t nvs_len, nvs_bytes_written, burst_len;
	int nvs_start, i;
	u32 dest_addr, val;
	u8 *nvs_ptr, *nvs;

	nvs = wl->nvs;
	if (nvs == NULL)
		return -ENODEV;

	nvs_ptr = nvs;

	nvs_len = wl->nvs_len;
	nvs_start = wl->fw_len;

	/*
	 * Layout before the actual NVS tables:
	 * 1 byte : burst length.
	 * 2 bytes: destination address.
	 * n bytes: data to burst copy.
	 *
	 * This is ended by a 0 length, then the NVS tables.
	 */

	while (nvs_ptr[0]) {
		burst_len = nvs_ptr[0];
		dest_addr = (nvs_ptr[1] & 0xfe) | ((u32)(nvs_ptr[2] << 8));

		/* We move our pointer to the data */
		nvs_ptr += 3;

		for (i = 0; i < burst_len; i++) {
			val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
			       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

			wl1251_debug(DEBUG_BOOT,
				     "nvs burst write 0x%x: 0x%x",
				     dest_addr, val);
			wl1251_mem_write32(wl, dest_addr, val);

			nvs_ptr += 4;
			dest_addr += 4;
		}
	}

	/*
	 * We've reached the first zero length, the first NVS table
	 * is 7 bytes further.
	 */
	nvs_ptr += 7;
	nvs_len -= nvs_ptr - nvs;
	nvs_len = ALIGN(nvs_len, 4);

	/* Now we must set the partition correctly */
	wl1251_set_partition(wl, nvs_start,
			     WL1251_PART_DOWN_MEM_SIZE,
			     WL1251_PART_DOWN_REG_START,
			     WL1251_PART_DOWN_REG_SIZE);

	/* And finally we upload the NVS tables */
	nvs_bytes_written = 0;
	while (nvs_bytes_written < nvs_len) {
		val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
		       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

		wl1251_debug(DEBUG_BOOT,
			     "nvs write table 0x%x: 0x%x",
			     nvs_start, val);
		wl1251_mem_write32(wl, nvs_start, val);

		nvs_ptr += 4;
		nvs_bytes_written += 4;
		nvs_start += 4;
	}

	return 0;
}