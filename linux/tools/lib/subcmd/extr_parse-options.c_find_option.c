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
struct option {scalar_t__ type; int short_name; scalar_t__ long_name; } ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct option *
find_option(struct option *opts, int shortopt, const char *longopt)
{
	for (; opts->type != OPTION_END; opts++) {
		if ((shortopt && opts->short_name == shortopt) ||
		    (opts->long_name && longopt &&
		     !strcmp(opts->long_name, longopt)))
			return opts;
	}
	return NULL;
}