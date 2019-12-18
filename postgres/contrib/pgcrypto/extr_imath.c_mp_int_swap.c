#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  single; int /*<<< orphan*/ * digits; } ;
typedef  TYPE_1__ mpz_t ;
typedef  TYPE_1__* mp_int ;

/* Variables and functions */
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 

void
mp_int_swap(mp_int a, mp_int c)
{
	if (a != c)
	{
		mpz_t		tmp = *a;

		*a = *c;
		*c = tmp;

		if (MP_DIGITS(a) == &(c->single))
			a->digits = &(a->single);
		if (MP_DIGITS(c) == &(a->single))
			c->digits = &(c->single);
	}
}