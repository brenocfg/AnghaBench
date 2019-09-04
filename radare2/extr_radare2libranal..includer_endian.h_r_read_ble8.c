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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  UT8_MAX ; 

__attribute__((used)) static inline ut8 r_read_ble8(const void *src) {
	if (!src) {
		return UT8_MAX;
	}
	return *(ut8 *)src;
}