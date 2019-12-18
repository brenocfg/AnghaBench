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
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_3__ {int alloc; int used; int /*<<< orphan*/  sign; scalar_t__ single; scalar_t__* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_BADARG ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_ZPOS ; 

mp_result
mp_int_init(mp_int z)
{
	if (z == NULL)
		return MP_BADARG;

	z->single = 0;
	z->digits = &(z->single);
	z->alloc = 1;
	z->used = 1;
	z->sign = MP_ZPOS;

	return MP_OK;
}