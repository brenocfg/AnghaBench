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
typedef  scalar_t__ ut64 ;
typedef  int ut32 ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ UT64_MAX ; 
 scalar_t__ c_addr ; 
 int /*<<< orphan*/  c_buff ; 
 scalar_t__ c_size ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  qnxr_write_memory (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int debug_qnx_write_at (const ut8 *buf, int sz, ut64 addr) {
	ut32 x, size_max = 500;
	ut32 packets = sz / size_max;
	ut32 last = sz % size_max;

	if (sz < 1 || addr >= UT64_MAX) {
		return -1;
	}
	if (c_addr != UT64_MAX && addr >= c_addr && c_addr + sz < (c_addr + c_size)) {
		R_FREE (c_buff);
		c_addr = UT64_MAX;
	}
	for (x = 0; x < packets; x++) {
		qnxr_write_memory (desc, addr + x * size_max,
				   (const uint8_t *)(buf + x * size_max), size_max);
	}
	if (last) {
		qnxr_write_memory (desc, addr + x * size_max,
				   (buf + x * size_max), last);
	}

	return sz;
}