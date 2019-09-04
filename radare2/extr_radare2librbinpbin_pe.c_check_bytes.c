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

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int const*,char*,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	unsigned int idx;
	if (!buf) {
		return false;
	}
	if (length <= 0x3d) {
		return false;
	}
	idx = (buf[0x3c] | (buf[0x3d]<<8));
	if (length > idx + 0x18 + 2) {
		/* Here PE signature for usual PE files
		 * and PL signature for Phar Lap TNT DOS extender 32bit executables
		 */
		if (!memcmp (buf, "MZ", 2)) {
			if (!memcmp (buf+idx, "PE", 2) &&
				!memcmp (buf + idx + 0x18, "\x0b\x01", 2)) {
				return true;
			}
			// TODO: Add one more indicator, to prevent false positives
			if (!memcmp (buf+idx, "PL", 2)) {
				return true;
			}
		}
	}
	return false;
}