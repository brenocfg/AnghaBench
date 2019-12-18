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
struct gc_arena {int dummy; } ;
struct client_nat_option_list {int n; struct client_nat_entry* entries; } ;
struct client_nat_entry {int /*<<< orphan*/  foreign_network; int /*<<< orphan*/  netmask; int /*<<< orphan*/  network; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA_NET_ORDER ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  print_in_addr_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

void
print_client_nat_list(const struct client_nat_option_list *list, int msglevel)
{
    struct gc_arena gc = gc_new();
    int i;

    msg(msglevel, "*** CNAT list");
    if (list)
    {
        for (i = 0; i < list->n; ++i)
        {
            const struct client_nat_entry *e = &list->entries[i];
            msg(msglevel, "  CNAT[%d] t=%d %s/%s/%s",
                i,
                e->type,
                print_in_addr_t(e->network, IA_NET_ORDER, &gc),
                print_in_addr_t(e->netmask, IA_NET_ORDER, &gc),
                print_in_addr_t(e->foreign_network, IA_NET_ORDER, &gc));
        }
    }
    gc_free(&gc);
}