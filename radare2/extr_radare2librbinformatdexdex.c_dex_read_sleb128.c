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

/* Variables and functions */
 int /*<<< orphan*/  SIG_EXTEND (int,int) ; 
 int dex_uleb128_len (int const*,int) ; 

int dex_read_sleb128(const char *ptr, int size) {
	int cur, result;
	ut8 len = dex_uleb128_len ((const ut8*)ptr, size);
	if (len > size) {
		return 0;
	}
	ptr += len - 1;
	result = *(ptr--);

	if (result <= 0x7f) {
		SIG_EXTEND (result, 25);
	} else {
		cur = *(ptr--);
		result = (result & 0x7f) | ((cur & 0x7f) << 7);
		if (cur <= 0x7f) {
			SIG_EXTEND (result, 18);
		} else {
			cur = *(ptr--);
			result |= (cur & 0x7f) << 14;
			if (cur <= 0x7f) {
				SIG_EXTEND (result, 11);
			} else {
				cur = *(ptr--);
				result |= (cur & 0x7f) << 21;
				if (cur <= 0x7f) {
					SIG_EXTEND (result, 4);
				} else {
					cur = *(ptr--);
					result |= cur << 28;
				}
			}
		}
	}
	return result;
}