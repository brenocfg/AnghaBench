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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int ordinal ;

/* Variables and functions */

__attribute__((used)) static inline void SET_LIBRARY_ORDINAL(uint16_t *n_desc, uint8_t ordinal) {
	*n_desc = (((*n_desc) & 0x00ff) | (((ordinal) & 0xff) << 8));
}