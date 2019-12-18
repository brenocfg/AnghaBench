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
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int SUCCESS ; 
 unsigned int if_nametoindex (char const*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

int php_string_to_if_index(const char *val, unsigned *out)
{
#if HAVE_IF_NAMETOINDEX
	unsigned int ind;

	ind = if_nametoindex(val);
	if (ind == 0) {
		php_error_docref(NULL, E_WARNING,
			"no interface with name \"%s\" could be found", val);
		return FAILURE;
	} else {
		*out = ind;
		return SUCCESS;
	}
#else
	php_error_docref(NULL, E_WARNING,
			"this platform does not support looking up an interface by "
			"name, an integer interface index must be supplied instead");
	return FAILURE;
#endif
}