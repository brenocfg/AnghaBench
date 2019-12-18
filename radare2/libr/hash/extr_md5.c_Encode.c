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
typedef  scalar_t__ ut8 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static void Encode(ut8 *output, ut32 *input, ut32 len) {
	ut32 i, j;
	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (ut8)(input[i] & 0xff);
		output[j+1] = (ut8)((input[i] >> 8) & 0xff);
		output[j+2] = (ut8)((input[i] >> 16) & 0xff);
		output[j+3] = (ut8)((input[i] >> 24) & 0xff);
	}
}