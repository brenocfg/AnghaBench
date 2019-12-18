#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_usmall ;
typedef  scalar_t__ mp_small ;
typedef  TYPE_1__* mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;
struct TYPE_4__ {int /*<<< orphan*/  sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NEG ; 
 int /*<<< orphan*/  s_ufake (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
s_fake(mp_int z, mp_small value, mp_digit vbuf[])
{
	mp_usmall	uv = (mp_usmall) (value < 0) ? -value : value;

	s_ufake(z, uv, vbuf);
	if (value < 0)
		z->sign = MP_NEG;
}