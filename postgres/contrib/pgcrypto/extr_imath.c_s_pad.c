#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_size ;
typedef  TYPE_1__* mp_int ;
typedef  scalar_t__ mp_digit ;
struct TYPE_5__ {scalar_t__ alloc; scalar_t__* digits; scalar_t__ single; } ;

/* Variables and functions */
 scalar_t__ MP_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_DIGITS (TYPE_1__*) ; 
 scalar_t__* s_alloc (scalar_t__) ; 
 scalar_t__* s_realloc (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ s_round_prec (scalar_t__) ; 

__attribute__((used)) static bool
s_pad(mp_int z, mp_size min)
{
	if (MP_ALLOC(z) < min)
	{
		mp_size		nsize = s_round_prec(min);
		mp_digit   *tmp;

		if (z->digits == &(z->single))
		{
			if ((tmp = s_alloc(nsize)) == NULL)
				return false;
			tmp[0] = z->single;
		}
		else if ((tmp = s_realloc(MP_DIGITS(z), MP_ALLOC(z), nsize)) == NULL)
		{
			return false;
		}

		z->digits = tmp;
		z->alloc = nsize;
	}

	return true;
}