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
struct options {int /*<<< orphan*/  ce; struct connection_list* connection_list; } ;
struct connection_list {int len; int /*<<< orphan*/ ** array; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SHOW_PARMS ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  show_connection_entry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_connection_entries(const struct options *o)
{
    if (o->connection_list)
    {
        const struct connection_list *l = o->connection_list;
        int i;
        for (i = 0; i < l->len; ++i)
        {
            msg(D_SHOW_PARMS, "Connection profiles [%d]:", i);
            show_connection_entry(l->array[i]);
        }
    }
    else
    {
        msg(D_SHOW_PARMS, "Connection profiles [default]:");
        show_connection_entry(&o->ce);
    }
    msg(D_SHOW_PARMS, "Connection profiles END");
}