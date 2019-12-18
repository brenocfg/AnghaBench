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
typedef  int /*<<< orphan*/  mp_usmall ;
typedef  int /*<<< orphan*/  mp_size ;
typedef  TYPE_1__* mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;
struct TYPE_3__ {int /*<<< orphan*/ * digits; int /*<<< orphan*/  sign; int /*<<< orphan*/  alloc; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VALUE_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  s_uvpack (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
s_ufake(mp_int z, mp_usmall value, mp_digit vbuf[])
{
	mp_size		ndig = (mp_size) s_uvpack(value, vbuf);

	z->used = ndig;
	z->alloc = MP_VALUE_DIGITS(value);
	z->sign = MP_ZPOS;
	z->digits = vbuf;
}