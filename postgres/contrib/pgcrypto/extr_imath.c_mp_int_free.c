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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_free (int /*<<< orphan*/ *) ; 

void
mp_int_free(mp_int z)
{
	assert(z != NULL);

	mp_int_clear(z);
	px_free(z);					/* note: NOT s_free() */
}