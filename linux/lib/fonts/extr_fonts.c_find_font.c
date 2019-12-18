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
struct font_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct font_desc const** fonts ; 
 unsigned int num_fonts ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct font_desc *find_font(const char *name)
{
	unsigned int i;

	BUILD_BUG_ON(!num_fonts);
	for (i = 0; i < num_fonts; i++)
		if (!strcmp(fonts[i]->name, name))
			return fonts[i];
	return NULL;
}