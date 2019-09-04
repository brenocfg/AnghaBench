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
typedef  void* uint ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct d11init {scalar_t__ addr; scalar_t__ size; int /*<<< orphan*/  value; } ;
struct brcms_hardware {int /*<<< orphan*/  unit; struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_write16 (struct bcma_device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_info (struct bcma_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_write_inits(struct brcms_hardware *wlc_hw,
				const struct d11init *inits)
{
	struct bcma_device *core = wlc_hw->d11core;
	int i;
	uint offset;
	u16 size;
	u32 value;

	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	for (i = 0; inits[i].addr != cpu_to_le16(0xffff); i++) {
		size = le16_to_cpu(inits[i].size);
		offset = le16_to_cpu(inits[i].addr);
		value = le32_to_cpu(inits[i].value);
		if (size == 2)
			bcma_write16(core, offset, value);
		else if (size == 4)
			bcma_write32(core, offset, value);
		else
			break;
	}
}