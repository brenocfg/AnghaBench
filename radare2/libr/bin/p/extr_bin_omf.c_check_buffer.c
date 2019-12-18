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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_bin_checksum_omf_ok (int const*,int) ; 
 int* r_buf_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int,int*,int) ; 
 int r_buf_read_le16_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int const*,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	int i;
	ut8 ch;
	if (r_buf_read_at (b, 0, &ch, 1) != 1) {
		return false;
	}
	if (ch != 0x80 && ch != 0x82) {
		return false;
	}
	ut16 rec_size = r_buf_read_le16_at (b, 1);
	ut8 str_size; (void)r_buf_read_at (b, 3, &str_size, 1);
	ut64 length = r_buf_size (b);
	if (str_size + 2 != rec_size || length < rec_size + 3) {
		return false;
	}
	// check that the string is ASCII
	for (i = 4; i < str_size + 4; i++) {
		if (r_buf_read_at (b, i, &ch, 1) != 1) {
			break;
		}
		if (ch > 0x7f) {
			return false;
		}
	}
	const ut8 *buf = r_buf_data (b, NULL);
	if (buf == NULL) {
		// hackaround until we make this plugin not use RBuf.data
		ut8 buf[1024] = {0};
		r_buf_read_at (b, 0, buf, sizeof (buf));
		return r_bin_checksum_omf_ok (buf, sizeof (buf));
	}
	r_return_val_if_fail (buf, false);
	return r_bin_checksum_omf_ok (buf, length);
}