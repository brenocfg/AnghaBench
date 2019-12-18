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
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 scalar_t__ CMPZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_result
mp_int_mod(mp_int a, mp_int m, mp_int c)
{
	DECLARE_TEMP(1);
	mp_int		out = (m == c) ? TEMP(0) : c;

	REQUIRE(mp_int_div(a, m, NULL, out));
	if (CMPZ(out) < 0)
	{
		REQUIRE(mp_int_add(out, m, c));
	}
	else
	{
		REQUIRE(mp_int_copy(out, c));
	}
	CLEANUP_TEMP();
	return MP_OK;
}