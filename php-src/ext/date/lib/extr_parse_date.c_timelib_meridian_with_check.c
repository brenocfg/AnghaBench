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
typedef  int timelib_sll ;

/* Variables and functions */
 int TIMELIB_UNSET ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

__attribute__((used)) static timelib_sll timelib_meridian_with_check(char **ptr, timelib_sll h)
{
	timelib_sll retval = 0;

	while (**ptr && !strchr("AaPp", **ptr)) {
		++*ptr;
	}
	if(!**ptr) {
		return TIMELIB_UNSET;
	}
	if (**ptr == 'a' || **ptr == 'A') {
		if (h == 12) {
			retval = -12;
		}
	} else if (h != 12) {
		retval = 12;
	}
	++*ptr;
	if (**ptr == '.') {
		++*ptr;
		if (**ptr != 'm' && **ptr != 'M') {
			return TIMELIB_UNSET;
		}
		++*ptr;
		if (**ptr != '.' ) {
			return TIMELIB_UNSET;
		}
		++*ptr;
	} else if (**ptr == 'm' || **ptr == 'M') {
		++*ptr;
	} else {
		return TIMELIB_UNSET;
	}
	return retval;
}