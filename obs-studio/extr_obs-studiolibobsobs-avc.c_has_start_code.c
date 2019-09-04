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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline bool has_start_code(const uint8_t *data)
{
	if (data[0] != 0 || data[1] != 0)
	       return false;

	return data[2] == 1 || (data[2] == 0 && data[3] == 1);
}