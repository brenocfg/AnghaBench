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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  (* RTLINITUNICODESTRINGFUNC ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;

/* Variables and functions */
 scalar_t__ get_nt_func (char*) ; 

__attribute__((used)) static void rtl_init_str(UNICODE_STRING *unistr, const wchar_t *str)
{
	static bool initialized = false;
	static RTLINITUNICODESTRINGFUNC func = NULL;

	if (!initialized) {
		func = (RTLINITUNICODESTRINGFUNC)get_nt_func(
			"RtlInitUnicodeString");
		initialized = true;
	}

	if (func)
		func(unistr, str);
}