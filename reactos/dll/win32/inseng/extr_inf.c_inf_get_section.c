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
struct inf_section {int /*<<< orphan*/  name; } ;
struct inf_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ inf_next_section (struct inf_file*,struct inf_section**) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

struct inf_section *inf_get_section(struct inf_file *inf, const char *name)
{
    struct inf_section *sec = NULL;

    while (inf_next_section(inf, &sec))
    {
        if (!strcasecmp(sec->name, name))
            return sec;
    }

    return NULL;
}