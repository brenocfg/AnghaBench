#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mp_int ;
struct TYPE_4__ {int /*<<< orphan*/ * digits; int /*<<< orphan*/  single; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  s_free (int /*<<< orphan*/ *) ; 

void
mp_int_clear(mp_int z)
{
	if (z == NULL)
		return;

	if (MP_DIGITS(z) != NULL)
	{
		if (MP_DIGITS(z) != &(z->single))
			s_free(MP_DIGITS(z));

		z->digits = NULL;
	}
}