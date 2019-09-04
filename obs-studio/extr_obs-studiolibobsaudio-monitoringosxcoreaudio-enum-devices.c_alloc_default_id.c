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
 int /*<<< orphan*/  UNUSED_PARAMETER (char const*) ; 
 char* bstrdup (char const*) ; 

__attribute__((used)) static bool alloc_default_id(void *data, const char *name, const char *id)
{
	char **p_id = data;
	UNUSED_PARAMETER(name);

	*p_id = bstrdup(id);
	return false;
}