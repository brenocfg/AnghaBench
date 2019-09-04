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
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read8_at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_pe64_buf(RBuffer *buf, ut64 length) {
	int idx, ret = false;
	if (!buf || length <= 0x3d) {
		return false;
	}
	idx = r_buf_read8_at (buf, 0x3c) | (r_buf_read8_at (buf, 0x3d)<<8);
	if (length >= idx + 0x20) {
		ut8 tmp1[2], tmp2[2], tmp3[2];
		r_buf_read_at (buf, 0, tmp1, 2);
		r_buf_read_at (buf, idx, tmp2, 2);
		r_buf_read_at (buf, idx + 0x18, tmp3, 2);
		if (!memcmp (tmp1, "MZ", 2) && !memcmp (tmp2, "PE", 2) && !memcmp (tmp3, "\x0b\x02", 2)) {
			ret = true;
		}
	}
	return ret;
}