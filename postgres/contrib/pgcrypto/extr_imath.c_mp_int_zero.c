#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mp_int ;
struct TYPE_3__ {int used; int /*<<< orphan*/  sign; scalar_t__* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
mp_int_zero(mp_int z)
{
	assert(z != NULL);

	z->digits[0] = 0;
	z->used = 1;
	z->sign = MP_ZPOS;
}