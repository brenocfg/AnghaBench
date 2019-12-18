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
typedef  int u64 ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void intel_pt_valid_str(char *str, size_t len, u64 valid)
{
	unsigned int val, last = 0, state = 1;
	int p = 0;

	str[0] = '\0';

	for (val = 0; val <= 64; val++, valid >>= 1) {
		if (valid & 1) {
			last = val;
			switch (state) {
			case 0:
				p += scnprintf(str + p, len - p, ",");
				/* Fall through */
			case 1:
				p += scnprintf(str + p, len - p, "%u", val);
				state = 2;
				break;
			case 2:
				state = 3;
				break;
			case 3:
				state = 4;
				break;
			default:
				break;
			}
		} else {
			switch (state) {
			case 3:
				p += scnprintf(str + p, len - p, ",%u", last);
				state = 0;
				break;
			case 4:
				p += scnprintf(str + p, len - p, "-%u", last);
				state = 0;
				break;
			default:
				break;
			}
			if (state != 1)
				state = 0;
		}
	}
}