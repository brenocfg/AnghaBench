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
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  r_mem_swapendian (int*,int*,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	bool ret = false;
	int off, version = 0;
	if (buf && length > 32 && !memcmp (buf, "\xca\xfe\xba\xbe", 4)) {
		// XXX not sure about endianness here
		memcpy (&off, buf + 4 * sizeof (int), sizeof (int));
		version = buf[6] | (buf[7] << 8);
		if (version > 1024) {
			// XXX is this correct in all cases? opposite of prev?
			r_mem_swapendian ((ut8 *) &off, (ut8 *) &off, sizeof (int));
			ret = true;
		}
	}
	return ret;
}