#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* from; char* to; } ;
typedef  TYPE_1__ substring_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RDMACG_MAX_STR ; 
 int /*<<< orphan*/  RDMACG_RESOURCE_MAX ; 
 int S32_MAX ; 
 int match_int (TYPE_1__*,int*) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdmacg_resource_names ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_resource(char *c, int *intval)
{
	substring_t argstr;
	char *name, *value = c;
	size_t len;
	int ret, i;

	name = strsep(&value, "=");
	if (!name || !value)
		return -EINVAL;

	i = match_string(rdmacg_resource_names, RDMACG_RESOURCE_MAX, name);
	if (i < 0)
		return i;

	len = strlen(value);

	argstr.from = value;
	argstr.to = value + len;

	ret = match_int(&argstr, intval);
	if (ret >= 0) {
		if (*intval < 0)
			return -EINVAL;
		return i;
	}
	if (strncmp(value, RDMACG_MAX_STR, len) == 0) {
		*intval = S32_MAX;
		return i;
	}
	return -EINVAL;
}