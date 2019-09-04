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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sony_backlight_props {int handle; unsigned char offset; int maxlvl; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned char*) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned char,...) ; 
 int /*<<< orphan*/  sony_find_snc_handle (int) ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 
 int sony_nc_buffer_call (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void sony_nc_backlight_ng_read_limits(int handle,
		struct sony_backlight_props *props)
{
	u64 offset;
	int i;
	int lvl_table_len = 0;
	u8 min = 0xff, max = 0x00;
	unsigned char buffer[32] = { 0 };

	props->handle = handle;
	props->offset = 0;
	props->maxlvl = 0xff;

	offset = sony_find_snc_handle(handle);

	/* try to read the boundaries from ACPI tables, if we fail the above
	 * defaults should be reasonable
	 */
	i = sony_nc_buffer_call(sony_nc_acpi_handle, "SN06", &offset, buffer,
			32);
	if (i < 0)
		return;

	switch (handle) {
	case 0x012f:
	case 0x0137:
		lvl_table_len = 9;
		break;
	case 0x143:
	case 0x14b:
	case 0x14c:
		lvl_table_len = 16;
		break;
	}

	/* the buffer lists brightness levels available, brightness levels are
	 * from position 0 to 8 in the array, other values are used by ALS
	 * control.
	 */
	for (i = 0; i < lvl_table_len && i < ARRAY_SIZE(buffer); i++) {

		dprintk("Brightness level: %d\n", buffer[i]);

		if (!buffer[i])
			break;

		if (buffer[i] > max)
			max = buffer[i];
		if (buffer[i] < min)
			min = buffer[i];
	}
	props->offset = min;
	props->maxlvl = max;
	dprintk("Brightness levels: min=%d max=%d\n", props->offset,
			props->maxlvl);
}