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
 int EINVAL ; 
 int STR_VAR_LEN_MAX ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,unsigned int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int synth_field_string_size(char *type)
{
	char buf[4], *end, *start;
	unsigned int len;
	int size, err;

	start = strstr(type, "char[");
	if (start == NULL)
		return -EINVAL;
	start += sizeof("char[") - 1;

	end = strchr(type, ']');
	if (!end || end < start)
		return -EINVAL;

	len = end - start;
	if (len > 3)
		return -EINVAL;

	strncpy(buf, start, len);
	buf[len] = '\0';

	err = kstrtouint(buf, 0, &size);
	if (err)
		return err;

	if (size > STR_VAR_LEN_MAX)
		return -EINVAL;

	return size;
}