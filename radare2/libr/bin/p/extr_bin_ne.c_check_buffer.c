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
typedef  scalar_t__ ut16 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_buf_read_le16_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut64 length = r_buf_size (b);
	if (length <= 0x3d) {
		return false;
	}
	ut16 idx = r_buf_read_le16_at (b, 0x3c);
	if ((ut64)idx + 26 < length) {
		ut8 buf[2];
		r_buf_read_at (b, 0, buf, sizeof (buf));
		if (!memcmp (buf, "MZ", 2)) {
			r_buf_read_at (b, idx, buf, sizeof (buf));
			if (!memcmp (buf, "NE", 2)) {
				return true;
			}
		}
	}
	return false;
}