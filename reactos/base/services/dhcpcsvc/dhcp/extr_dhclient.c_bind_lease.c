#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct interface_info {TYPE_1__* client; } ;
struct client_lease {scalar_t__ renewal; int /*<<< orphan*/  address; int /*<<< orphan*/  medium; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; struct client_lease* active; struct client_lease* new; int /*<<< orphan*/  medium; } ;
typedef  scalar_t__ PDHCP_ADAPTER ;

/* Variables and functions */
 scalar_t__ AdapterFindInfo (struct interface_info*) ; 
 int /*<<< orphan*/  S_BOUND ; 
 int /*<<< orphan*/  add_timeout (scalar_t__,int /*<<< orphan*/ ,struct interface_info*) ; 
 int /*<<< orphan*/  free_client_lease (struct client_lease*) ; 
 int /*<<< orphan*/  note (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  piaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_domain (scalar_t__,struct client_lease*) ; 
 int /*<<< orphan*/  set_name_servers (scalar_t__,struct client_lease*) ; 
 int /*<<< orphan*/  setup_adapter (scalar_t__,struct client_lease*) ; 
 int /*<<< orphan*/  state_bound ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  warning (char*,struct interface_info*) ; 

void
bind_lease(struct interface_info *ip)
{
    PDHCP_ADAPTER Adapter;
    struct client_lease *new_lease = ip->client->new;
    time_t cur_time;

    time(&cur_time);

    /* Remember the medium. */
    ip->client->new->medium = ip->client->medium;

    /* Replace the old active lease with the new one. */
    if (ip->client->active)
        free_client_lease(ip->client->active);
    ip->client->active = ip->client->new;
    ip->client->new = NULL;

    /* Set up a timeout to start the renewal process. */
    /* Timeout of zero means no timeout (some implementations seem to use
     * one day).
     */
    if( ip->client->active->renewal - cur_time )
        add_timeout(ip->client->active->renewal, state_bound, ip);

    note("bound to %s -- renewal in %ld seconds.",
         piaddr(ip->client->active->address),
         (long int)(ip->client->active->renewal - cur_time));

    ip->client->state = S_BOUND;

    Adapter = AdapterFindInfo( ip );

    if( Adapter )  setup_adapter( Adapter, new_lease );
    else {
        warning("Could not find adapter for info %p\n", ip);
        return;
    }
    set_name_servers( Adapter, new_lease );
    set_domain( Adapter, new_lease );
}