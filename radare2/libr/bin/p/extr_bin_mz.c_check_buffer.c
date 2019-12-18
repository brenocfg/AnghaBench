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
typedef  int ut16 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  checkEntrypointBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ knownHeaderBuffer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_buf_read_le16_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	r_return_val_if_fail (b, false);
	ut64 b_size = r_buf_size (b);
	if (b_size <= 0x3d) {
		return false;
	}

	// Check for MZ magic.
	ut8 h[2];
	if (r_buf_read_at (b, 0, h, 2) != 2) {
		return false;
	}
	if (memcmp (h, "MZ", 2)) {
		return false;
	}

	// See if there is a new exe header.
	ut16 new_exe_header_offset = r_buf_read_le16_at (b, 0x3c);
	if (b_size > new_exe_header_offset + 2) {
		if (knownHeaderBuffer (b, new_exe_header_offset)) {
			return false;
		}
	}

	// Raw plain MZ executable (watcom)
	if (!checkEntrypointBuffer (b)) {
		return false;
	}
	return true;
}