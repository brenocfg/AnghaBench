#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nfonts; TYPE_1__** fonts; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ FONScontext ;

/* Variables and functions */
 int FONS_INVALID ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int fonsGetFontByName(FONScontext* s, const char* name)
{
	int i;
	for (i = 0; i < s->nfonts; i++) {
		if (strcmp(s->fonts[i]->name, name) == 0)
			return i;
	}
	return FONS_INVALID;
}