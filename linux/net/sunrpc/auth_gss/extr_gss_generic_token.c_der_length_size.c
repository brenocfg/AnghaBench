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

/* Variables and functions */

__attribute__((used)) static int
der_length_size( int length)
{
	if (length < (1<<7))
		return 1;
	else if (length < (1<<8))
		return 2;
#if (SIZEOF_INT == 2)
	else
		return 3;
#else
	else if (length < (1<<16))
		return 3;
	else if (length < (1<<24))
		return 4;
	else
		return 5;
#endif
}