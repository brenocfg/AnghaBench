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
typedef  scalar_t__ uint8_t ;
typedef  unsigned long uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t sid_to_key(const uint8_t *s_id)
{
	uint32_t key;

	key = (((unsigned long)s_id[0] << 16) |
	       ((unsigned long)s_id[1] << 8) |
	       (unsigned long)s_id[2]);
	return key;
}