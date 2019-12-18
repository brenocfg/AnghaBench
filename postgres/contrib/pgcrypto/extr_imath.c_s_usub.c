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
typedef  int mp_word ;
typedef  scalar_t__ mp_size ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 scalar_t__ LOWER_HALF (int) ; 
 scalar_t__ MP_DIGIT_MAX ; 
 scalar_t__ UPPER_HALF (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
s_usub(mp_digit *da, mp_digit *db, mp_digit *dc, mp_size size_a,
	   mp_size size_b)
{
	mp_size		pos;
	mp_word		w = 0;

	/* We assume that |a| >= |b| so this should definitely hold */
	assert(size_a >= size_b);

	/* Subtract corresponding digits and propagate borrow */
	for (pos = 0; pos < size_b; ++pos, ++da, ++db, ++dc)
	{
		w = ((mp_word) MP_DIGIT_MAX + 1 +	/* MP_RADIX */
			 (mp_word) *da) -
			w - (mp_word) *db;

		*dc = LOWER_HALF(w);
		w = (UPPER_HALF(w) == 0);
	}

	/* Finish the subtraction for remaining upper digits of da */
	for ( /* */ ; pos < size_a; ++pos, ++da, ++dc)
	{
		w = ((mp_word) MP_DIGIT_MAX + 1 +	/* MP_RADIX */
			 (mp_word) *da) -
			w;

		*dc = LOWER_HALF(w);
		w = (UPPER_HALF(w) == 0);
	}

	/* If there is a borrow out at the end, it violates the precondition */
	assert(w == 0);
}