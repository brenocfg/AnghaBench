#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  unsigned int ut64 ;
typedef  int ut16 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int* r_buf_data (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int haschr(const RBinFile* bf, ut16 dllCharacteristic) {
	const ut8 *buf;
	unsigned int idx;
	ut64 sz;
	if (!bf) {
		return false;
	}
	buf = r_buf_data (bf->buf, &sz);
	if (!buf) {
		return false;
	}
	idx = (buf[0x3c] | (buf[0x3d]<<8));
	if (idx + 0x5E + 1 >= sz ) {
		return false;
	}
	//it's funny here idx+0x5E can be 158 and sz 159 but with
	//the cast it reads two bytes until 160
	return ((*(ut16*)(buf + idx + 0x5E)) & dllCharacteristic);
}