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

__attribute__((used)) static void Decode(ut32 *output, const ut8 *input, ut32 len) {
	ut32 i, j;
	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[i] = ((ut32)input[j]) | (((ut32)input[j + 1]) << 8) |
			    (((ut32)input[j + 2]) << 16) |
			    (((ut32)input[j + 3]) << 24);
	}
}