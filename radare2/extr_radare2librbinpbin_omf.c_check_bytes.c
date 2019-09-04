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
typedef  int ut16 ;

/* Variables and functions */
 int r_bin_checksum_omf_ok (int const*,int) ; 
 int ut8p_bw (int const*) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	int i;
	if (!buf || length < 4) {
		return false;
	}
	if ((*buf != 0x80 && *buf != 0x82) || length < 4) {
		return false;
	}
	ut16 rec_size = ut8p_bw (buf + 1);
	ut8 str_size = *(buf + 3);
	if (str_size + 2 != rec_size || length < rec_size + 3) {
		return false;
	}
	// check that the string is ASCII
	for (i = 4; i < str_size + 4; ++i) {
		if (buf[i] > 0x7f) {
			return false;
		}
	}
	return r_bin_checksum_omf_ok (buf, length);
}