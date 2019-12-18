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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int MP_DIGIT_BIT ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int MP_USED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_2expt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_pad (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static mp_result
s_brmu(mp_int z, mp_int m)
{
	mp_size		um = MP_USED(m) * 2;

	if (!s_pad(z, um))
		return MP_MEMORY;

	s_2expt(z, MP_DIGIT_BIT * um);
	return mp_int_div(z, m, z, NULL);
}