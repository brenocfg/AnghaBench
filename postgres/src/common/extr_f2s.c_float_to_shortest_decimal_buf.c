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
 int /*<<< orphan*/  Assert (int) ; 
 int const FLOAT_SHORTEST_DECIMAL_LEN ; 
 int float_to_shortest_decimal_bufn (float,char*) ; 

int
float_to_shortest_decimal_buf(float f, char *result)
{
	const int	index = float_to_shortest_decimal_bufn(f, result);

	/* Terminate the string. */
	Assert(index < FLOAT_SHORTEST_DECIMAL_LEN);
	result[index] = '\0';
	return index;
}