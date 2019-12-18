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
typedef  size_t ut8 ;

/* Variables and functions */
 size_t* ebcdic_to_ascii ; 

__attribute__((used)) static void from_ebcdic(const ut8 *buf, size_t nbytes, ut8 *out) {
	size_t i;
	for (i = 0; i < nbytes; i++) {
		out[i] = ebcdic_to_ascii[buf[i]];
	}
}