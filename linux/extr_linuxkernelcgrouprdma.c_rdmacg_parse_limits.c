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

/* Variables and functions */
 unsigned long BIT (int) ; 
 int EINVAL ; 
 int parse_resource (char*,int*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int rdmacg_parse_limits(char *options,
			       int *new_limits, unsigned long *enables)
{
	char *c;
	int err = -EINVAL;

	/* parse resource options */
	while ((c = strsep(&options, " ")) != NULL) {
		int index, intval;

		index = parse_resource(c, &intval);
		if (index < 0)
			goto err;

		new_limits[index] = intval;
		*enables |= BIT(index);
	}
	return 0;

err:
	return err;
}