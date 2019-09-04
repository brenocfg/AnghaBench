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
 int /*<<< orphan*/  free (char*) ; 
 int sysfs__read_str (char const*,char**,size_t*) ; 

int sysfs__read_bool(const char *entry, bool *value)
{
	char *buf;
	size_t size;
	int ret;

	ret = sysfs__read_str(entry, &buf, &size);
	if (ret < 0)
		return ret;

	switch (buf[0]) {
	case '1':
	case 'y':
	case 'Y':
		*value = true;
		break;
	case '0':
	case 'n':
	case 'N':
		*value = false;
		break;
	default:
		ret = -1;
	}

	free(buf);

	return ret;
}