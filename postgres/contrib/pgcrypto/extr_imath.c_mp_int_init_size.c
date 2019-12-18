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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_5__ {int used; int alloc; int /*<<< orphan*/  sign; scalar_t__* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int default_precision ; 
 int /*<<< orphan*/  mp_int_init (TYPE_1__*) ; 
 scalar_t__* s_alloc (int) ; 
 int s_round_prec (int) ; 

mp_result
mp_int_init_size(mp_int z, mp_size prec)
{
	assert(z != NULL);

	if (prec == 0)
	{
		prec = default_precision;
	}
	else if (prec == 1)
	{
		return mp_int_init(z);
	}
	else
	{
		prec = s_round_prec(prec);
	}

	z->digits = s_alloc(prec);
	if (MP_DIGITS(z) == NULL)
		return MP_MEMORY;

	z->digits[0] = 0;
	z->used = 1;
	z->alloc = prec;
	z->sign = MP_ZPOS;

	return MP_OK;
}