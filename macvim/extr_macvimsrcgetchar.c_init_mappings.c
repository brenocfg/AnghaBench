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

void
init_mappings()
{
#if defined(MSDOS) || defined(MSWIN) || defined(OS2) || defined(MACOS)
    int		i;

    for (i = 0; i < sizeof(initmappings) / sizeof(struct initmap); ++i)
	add_map(initmappings[i].arg, initmappings[i].mode);
#endif
}