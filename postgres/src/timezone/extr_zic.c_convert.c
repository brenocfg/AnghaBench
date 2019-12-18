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
typedef  int int32 ;

/* Variables and functions */

__attribute__((used)) static void
convert(const int32 val, char *const buf)
{
	int			i;
	int			shift;
	unsigned char *const b = (unsigned char *) buf;

	for (i = 0, shift = 24; i < 4; ++i, shift -= 8)
		b[i] = val >> shift;
}