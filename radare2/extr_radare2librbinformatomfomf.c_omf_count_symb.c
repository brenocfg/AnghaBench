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
typedef  int ut32 ;
typedef  int ut16 ;

/* Variables and functions */

__attribute__((used)) static ut32 omf_count_symb(ut16 total_size, ut32 ct, const ut8 *buf, int bits) {
	ut32 nb_symb = 0;
	while (ct < total_size - 1) {
		ct += buf[ct] + 1 + (bits == 32 ? 4 : 2);
		if (ct > total_size - 1) {
			return nb_symb;
		}
		if (buf[ct] & 0x80) {
			ct += 2;
		} else {
			ct++;
		}
		nb_symb++;
	}
	return nb_symb;
}