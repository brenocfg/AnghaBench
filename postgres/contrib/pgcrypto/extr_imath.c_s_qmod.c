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
typedef  TYPE_1__* mp_int ;
typedef  unsigned int mp_digit ;
struct TYPE_5__ {int used; unsigned int* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int MP_DIGIT_BIT ; 
 int MP_USED (TYPE_1__*) ; 

__attribute__((used)) static void
s_qmod(mp_int z, mp_size p2)
{
	mp_size		start = p2 / MP_DIGIT_BIT + 1,
				rest = p2 % MP_DIGIT_BIT;
	mp_size		uz = MP_USED(z);
	mp_digit	mask = (1u << rest) - 1;

	if (start <= uz)
	{
		z->used = start;
		z->digits[start - 1] &= mask;
		CLAMP(z);
	}
}