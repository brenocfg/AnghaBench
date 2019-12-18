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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int* bytes ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int sz ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	return false;
#if 0
	if (!bytes) {
		return false;
	}
	if (sz <= 0x3d) { //less than size of MS-DOS header which is 64bytes
		return false;
	}
	ut32 idx = (bytes[0x3c] | (bytes[0x3d]<<8));
	if (sz > idx + 0x18 + 2) {
		/* Here PE signature for usual PE files
		 * and PL signature for Phar Lap TNT DOS extender 32bit executables
		 */
		if (!memcmp (bytes, "MZ", 2)) {
			if (!memcmp (bytes+idx, "PE", 2) &&
				!memcmp (bytes+idx+0x18, "\x0b\x01", 2)) {
				return true;
			}
			// TODO: Add one more indicator, to prevent false positives
			if (!memcmp (bytes+idx, "PL", 2)) {
				return true;
			}
		}
	}
	return false;
#endif
}