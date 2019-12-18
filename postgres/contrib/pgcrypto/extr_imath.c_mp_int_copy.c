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
typedef  int /*<<< orphan*/  mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;
struct TYPE_7__ {int /*<<< orphan*/  sign; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int /*<<< orphan*/ ) ; 

mp_result
mp_int_copy(mp_int a, mp_int c)
{
	assert(a != NULL && c != NULL);

	if (a != c)
	{
		mp_size		ua = MP_USED(a);
		mp_digit   *da,
				   *dc;

		if (!s_pad(c, ua))
			return MP_MEMORY;

		da = MP_DIGITS(a);
		dc = MP_DIGITS(c);
		COPY(da, dc, ua);

		c->used = ua;
		c->sign = a->sign;
	}

	return MP_OK;
}