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
struct client_nat_option_list {int n; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry (struct client_nat_option_list*,int /*<<< orphan*/ *) ; 

void
copy_client_nat_option_list(struct client_nat_option_list *dest,
                            const struct client_nat_option_list *src)
{
    int i;
    for (i = 0; i < src->n; ++i)
    {
        if (!add_entry(dest, &src->entries[i]))
        {
            break;
        }
    }
}