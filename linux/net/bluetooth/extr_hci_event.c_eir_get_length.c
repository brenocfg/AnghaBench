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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static inline size_t eir_get_length(u8 *eir, size_t eir_len)
{
	size_t parsed = 0;

	while (parsed < eir_len) {
		u8 field_len = eir[0];

		if (field_len == 0)
			return parsed;

		parsed += field_len + 1;
		eir += field_len + 1;
	}

	return eir_len;
}