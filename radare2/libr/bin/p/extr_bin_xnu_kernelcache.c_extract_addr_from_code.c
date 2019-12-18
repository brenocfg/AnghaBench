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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;

/* Variables and functions */
 int r_read_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 extract_addr_from_code(ut8 *arm64_code, ut64 vaddr) {
	ut64 addr = vaddr & ~0xfff;

	ut64 adrp = r_read_le32 (arm64_code);
	ut64 adrp_offset = ((adrp & 0x60000000) >> 29) | ((adrp & 0xffffe0) >> 3);
	addr += adrp_offset << 12;

	ut64 ldr = r_read_le32 (arm64_code + 4);
	addr += ((ldr & 0x3ffc00) >> 10) << ((ldr & 0xc0000000) >> 30);

	return addr;
}