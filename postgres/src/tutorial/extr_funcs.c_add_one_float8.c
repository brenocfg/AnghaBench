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
typedef  scalar_t__ float8 ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

float8 *
add_one_float8(float8 *arg)
{
	float8	   *result = (float8 *) palloc(sizeof(float8));

	*result = *arg + 1.0;

	return result;
}