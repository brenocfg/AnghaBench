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
struct intlist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int intlist__add (struct intlist*,long) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static int intlist__parse_list(struct intlist *ilist, const char *s)
{
	char *sep;
	int err;

	do {
		long value = strtol(s, &sep, 10);
		err = -EINVAL;
		if (*sep != ',' && *sep != '\0')
			break;
		err = intlist__add(ilist, value);
		if (err)
			break;
		s = sep + 1;
	} while (*sep != '\0');

	return err;
}