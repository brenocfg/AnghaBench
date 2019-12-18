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
typedef  int /*<<< orphan*/  mp_usmall ;
typedef  scalar_t__ mp_small ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int s_uvcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
s_vcmp(mp_int a, mp_small v)
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)
#endif
	mp_usmall	uv = (v < 0) ? -(mp_usmall) v : (mp_usmall) v;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	return s_uvcmp(a, uv);
}