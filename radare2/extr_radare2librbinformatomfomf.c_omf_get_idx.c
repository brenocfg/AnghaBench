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
typedef  int const ut16 ;

/* Variables and functions */

__attribute__((used)) static ut16 omf_get_idx(const ut8 *buf, int buf_size) {
	if (buf_size < 2) {
		return 0;
	}
	if (*buf & 0x80) {
		return (ut16)((*buf & 0x7f) * 0x100 + buf[1]);
	}
	return *buf;
}