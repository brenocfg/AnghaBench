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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int check_sd_current_prior(u32 sd_current_prior)
{
	bool fake_para = false;
	int i;

	for (i = 0; i < 4; i++) {
		u8 tmp = (u8)(sd_current_prior >> (i * 8));

		if (tmp > 0x03) {
			fake_para = true;
			break;
		}
	}

	return !fake_para;
}