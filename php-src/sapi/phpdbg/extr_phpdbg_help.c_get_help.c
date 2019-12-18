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
struct TYPE_3__ {char* text; scalar_t__ key; } ;
typedef  TYPE_1__ phpdbg_help_text_t ;

/* Variables and functions */
 TYPE_1__* phpdbg_help_text ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const* const) ; 

__attribute__((used)) static char *get_help(const char * const key)
{
	phpdbg_help_text_t *p;

	/* Note that phpdbg_help_text is not assumed to be collated in key order.  This is an
	   inconvience that means that help can't be logically grouped Not worth
	   the savings */

	for (p = phpdbg_help_text; p->key; p++) {
		if (!strcmp(p->key, key)) {
			return p->text;
		}
	}
	return "";   /* return empty string to denote no match found */
}