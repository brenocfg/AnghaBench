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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_EMPTY_SCAN_SIZE ; 

__attribute__((used)) static inline uint32_t EMPTY_SCAN_SIZE(uint32_t sector_size) {
	if (sector_size < DEFAULT_EMPTY_SCAN_SIZE)
		return sector_size;
	else
		return DEFAULT_EMPTY_SCAN_SIZE;
}