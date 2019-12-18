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
typedef  int ut16 ;

/* Variables and functions */
 int UT16_MAX ; 

__attribute__((used)) static inline ut16 r_read_me16(const void *src) {
	if (!src) {
		return UT16_MAX;
	}
	const ut8 *s = (const ut8*)src;
	return (((ut16)s[0]) << 8) | (((ut16)s[1]) << 0);
}