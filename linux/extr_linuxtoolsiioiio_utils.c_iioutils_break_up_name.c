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
 int ARRAY_SIZE (char**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** iio_direction ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strtok (char*,char*) ; 

int iioutils_break_up_name(const char *full_name, char **generic_name)
{
	char *current;
	char *w, *r;
	char *working, *prefix = "";
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(iio_direction); i++)
		if (!strncmp(full_name, iio_direction[i],
			     strlen(iio_direction[i]))) {
			prefix = iio_direction[i];
			break;
		}

	current = strdup(full_name + strlen(prefix) + 1);
	if (!current)
		return -ENOMEM;

	working = strtok(current, "_\0");
	if (!working) {
		free(current);
		return -EINVAL;
	}

	w = working;
	r = working;

	while (*r != '\0') {
		if (!isdigit(*r)) {
			*w = *r;
			w++;
		}

		r++;
	}
	*w = '\0';
	ret = asprintf(generic_name, "%s_%s", prefix, working);
	free(current);

	return (ret == -1) ? -ENOMEM : 0;
}