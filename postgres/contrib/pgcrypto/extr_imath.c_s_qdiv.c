#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_size ;
typedef  TYPE_1__* mp_int ;
typedef  scalar_t__ mp_digit ;
struct TYPE_7__ {scalar_t__* digits; int /*<<< orphan*/  sign; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 scalar_t__* MP_DIGITS (TYPE_1__*) ; 
 scalar_t__ MP_DIGIT_BIT ; 
 int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 

__attribute__((used)) static void
s_qdiv(mp_int z, mp_size p2)
{
	mp_size		ndig = p2 / MP_DIGIT_BIT,
				nbits = p2 % MP_DIGIT_BIT;
	mp_size		uz = MP_USED(z);

	if (ndig)
	{
		mp_size		mark;
		mp_digit   *to,
				   *from;

		if (ndig >= uz)
		{
			mp_int_zero(z);
			return;
		}

		to = MP_DIGITS(z);
		from = to + ndig;

		for (mark = ndig; mark < uz; ++mark)
		{
			*to++ = *from++;
		}

		z->used = uz - ndig;
	}

	if (nbits)
	{
		mp_digit	d = 0,
				   *dz,
					save;
		mp_size		up = MP_DIGIT_BIT - nbits;

		uz = MP_USED(z);
		dz = MP_DIGITS(z) + uz - 1;

		for ( /* */ ; uz > 0; --uz, --dz)
		{
			save = *dz;

			*dz = (*dz >> nbits) | (d << up);
			d = save;
		}

		CLAMP(z);
	}

	if (MP_USED(z) == 1 && z->digits[0] == 0)
		z->sign = MP_ZPOS;
}