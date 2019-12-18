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
struct mp_log {int dummy; } ;
struct m_property {int name; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

void m_properties_print_help_list(struct mp_log *log,
                                  const struct m_property *list)
{
    int count = 0;

    mp_info(log, "Name\n\n");
    for (int i = 0; list[i].name; i++) {
        const struct m_property *p = &list[i];
        mp_info(log, " %s\n", p->name);
        count++;
    }
    mp_info(log, "\nTotal: %d properties\n", count);
}