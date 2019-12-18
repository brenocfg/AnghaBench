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
typedef  int const ut64 ;
typedef  int ut16 ;

/* Variables and functions */

__attribute__((used)) static ut64 r_bin_mz_va_to_la(const ut16 segment, const ut16 offset) {
	return (segment << 4) + offset;
}