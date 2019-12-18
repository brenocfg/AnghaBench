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
struct client_nat_option_list {int dummy; } ;
struct client_nat_entry {void* foreign_network; void* netmask; void* network; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DNAT ; 
 int /*<<< orphan*/  CN_SNAT ; 
 int /*<<< orphan*/  add_entry (struct client_nat_option_list*,struct client_nat_entry*) ; 
 void* getaddr (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void
add_client_nat_to_option_list(struct client_nat_option_list *dest,
                              const char *type,
                              const char *network,
                              const char *netmask,
                              const char *foreign_network,
                              int msglevel)
{
    struct client_nat_entry e;
    bool ok;

    if (!strcmp(type, "snat"))
    {
        e.type = CN_SNAT;
    }
    else if (!strcmp(type, "dnat"))
    {
        e.type = CN_DNAT;
    }
    else
    {
        msg(msglevel, "client-nat: type must be 'snat' or 'dnat'");
        return;
    }

    e.network = getaddr(0, network, 0, &ok, NULL);
    if (!ok)
    {
        msg(msglevel, "client-nat: bad network: %s", network);
        return;
    }
    e.netmask = getaddr(0, netmask, 0, &ok, NULL);
    if (!ok)
    {
        msg(msglevel, "client-nat: bad netmask: %s", netmask);
        return;
    }
    e.foreign_network = getaddr(0, foreign_network, 0, &ok, NULL);
    if (!ok)
    {
        msg(msglevel, "client-nat: bad foreign network: %s", foreign_network);
        return;
    }

    add_entry(dest, &e);
}