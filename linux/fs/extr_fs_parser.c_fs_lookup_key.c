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
struct fs_parameter_spec {scalar_t__ name; } ;
struct fs_parameter_description {struct fs_parameter_spec* specs; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static const struct fs_parameter_spec *fs_lookup_key(
	const struct fs_parameter_description *desc,
	const char *name)
{
	const struct fs_parameter_spec *p;

	if (!desc->specs)
		return NULL;

	for (p = desc->specs; p->name; p++)
		if (strcmp(p->name, name) == 0)
			return p;

	return NULL;
}