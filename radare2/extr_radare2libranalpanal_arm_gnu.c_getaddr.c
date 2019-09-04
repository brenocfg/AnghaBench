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
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int st32 ;

/* Variables and functions */

__attribute__((used)) static ut64 getaddr(ut64 addr, const ut8 *d) {
	if (d[2] >> 7) {
		/// st32 n = (d[0] + (d[1] << 8) + (d[2] << 16) + (0xff << 24));
		st32 n = (d[0] + (d[1] << 8) + (d[2] << 16) + ((ut64)(0xff) << 24)); // * 16777216));
		n = -n;
		return addr - (n * 4);
	}
	return addr + (4 * (d[0] + (d[1] << 8) + (d[2] << 16)));
}