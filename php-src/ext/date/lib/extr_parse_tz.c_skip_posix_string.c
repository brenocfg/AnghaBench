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
typedef  int /*<<< orphan*/  timelib_tzinfo ;

/* Variables and functions */

__attribute__((used)) static void skip_posix_string(const unsigned char **tzf, timelib_tzinfo *tz)
{
	int n_count = 0;

	do {
		if (*tzf[0] == '\n') {
			n_count++;
		}
		(*tzf)++;
	} while (n_count < 2);
}