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

__attribute__((used)) static inline int needWord(ut8 type) {
	return ((type <= 0x17) && (type > 0x0f)) \
		|| (type == 0x1e) || (type == 0x1f);
}