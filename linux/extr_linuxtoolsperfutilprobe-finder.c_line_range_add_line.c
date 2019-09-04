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
struct line_range {int /*<<< orphan*/  line_list; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int ENOMEM ; 
 int intlist__add (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int line_range_add_line(const char *src, unsigned int lineno,
			       struct line_range *lr)
{
	/* Copy source path */
	if (!lr->path) {
		lr->path = strdup(src);
		if (lr->path == NULL)
			return -ENOMEM;
	}
	return intlist__add(lr->line_list, lineno);
}