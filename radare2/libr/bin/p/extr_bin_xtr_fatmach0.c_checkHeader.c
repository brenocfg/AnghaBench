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
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int r_buf_read_be32_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool checkHeader(RBuffer *b) {
	ut8 buf[4];
	const ut64 sz = r_buf_size (b);
	r_buf_read_at (b, 0, buf, 4);
	if (sz >= 0x300 && !memcmp (buf, "\xca\xfe\xba\xbe", 4)) {
		ut64 addr = 4 * sizeof (32);
		ut64 off = r_buf_read_be32_at (b, addr);
		if (off > 0 && off + 4 < sz) {
			ut64 h = 0;
			r_buf_read_at (b, h + off, buf, 4);
			if (!memcmp (buf, "\xce\xfa\xed\xfe", 4) ||
				!memcmp (buf, "\xfe\xed\xfa\xce", 4) ||
				!memcmp (buf, "\xfe\xed\xfa\xcf", 4) ||
				!memcmp (buf, "\xcf\xfa\xed\xfe", 4)) {
				return true;
			}
		}
	}
	return false;
}