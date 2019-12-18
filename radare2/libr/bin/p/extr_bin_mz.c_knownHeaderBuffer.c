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
typedef  scalar_t__ ut16 ;
typedef  int /*<<< orphan*/  h ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool knownHeaderBuffer(RBuffer *b, ut16 offset) {
	ut8 h[2];
	if (r_buf_read_at (b, offset, h, sizeof (h)) != sizeof (h)) {
		return false;
	}
	if (!memcmp (h, "PE", 2)) {
		if (offset + 0x20 < r_buf_size (b)) {
			if (r_buf_read_at (b, offset + 0x18, h, sizeof (h)) != 2) {
				return false;
			}
			if (!memcmp (h, "\x0b\x01", 2)) {
				return true;
			}
		}
	} else {
		if (!memcmp (h, "NE", 2)
		 || !memcmp (h, "LE", 2)
		 || !memcmp (h, "LX", 2)
		 || !memcmp (h, "PL", 2)) {
			return true;
		}
	}
	return false;
}