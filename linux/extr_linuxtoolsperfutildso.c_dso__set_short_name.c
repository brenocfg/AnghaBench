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
struct dso {int short_name_allocated; char const* short_name; int /*<<< orphan*/  short_name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void dso__set_short_name(struct dso *dso, const char *name, bool name_allocated)
{
	if (name == NULL)
		return;

	if (dso->short_name_allocated)
		free((char *)dso->short_name);

	dso->short_name		  = name;
	dso->short_name_len	  = strlen(name);
	dso->short_name_allocated = name_allocated;
}