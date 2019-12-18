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
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int s_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mp_int_compare_unsigned(mp_int a, mp_int b)
{
	assert(a != NULL && b != NULL);

	return s_ucmp(a, b);
}