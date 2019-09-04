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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int KDB_BADINT ; 
 int /*<<< orphan*/  simple_strtoull (char const*,char**,int) ; 

int kdbgetu64arg(const char *arg, u64 *value)
{
	char *endp;
	u64 val;

	val = simple_strtoull(arg, &endp, 0);

	if (endp == arg) {

		val = simple_strtoull(arg, &endp, 16);
		if (endp == arg)
			return KDB_BADINT;
	}

	*value = val;

	return 0;
}