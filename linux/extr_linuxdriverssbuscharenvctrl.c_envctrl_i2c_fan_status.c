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
struct i2c_child_t {unsigned char fan_mask; } ;

/* Variables and functions */
 unsigned char ENVCTRL_ALL_FANS_BAD ; 
 unsigned char ENVCTRL_ALL_FANS_GOOD ; 
 int PCF8584_MAX_CHANNELS ; 
 int* chnls_mask ; 

__attribute__((used)) static int envctrl_i2c_fan_status(struct i2c_child_t *pchild,
				  unsigned char data,
				  char *bufdata)
{
	unsigned char tmp, ret = 0;
	int i, j = 0;

	tmp = data & pchild->fan_mask;

	if (tmp == pchild->fan_mask) {
		/* All bits are on. All fans are functioning. */
		ret = ENVCTRL_ALL_FANS_GOOD;
	} else if (tmp == 0) {
		/* No bits are on. No fans are functioning. */
		ret = ENVCTRL_ALL_FANS_BAD;
	} else {
		/* Go through all channels, mark 'on' the matched bits.
		 * Notice that fan_mask may have discontiguous bits but
		 * return mask are always contiguous. For example if we
		 * monitor 4 fans at channels 0,1,2,4, the return mask
		 * should be 00010000 if only fan at channel 4 is working.
		 */
		for (i = 0; i < PCF8584_MAX_CHANNELS;i++) {
			if (pchild->fan_mask & chnls_mask[i]) {
				if (!(chnls_mask[i] & tmp))
					ret |= chnls_mask[j];

				j++;
			}
		}
	}

	bufdata[0] = ret;
	return 1;
}