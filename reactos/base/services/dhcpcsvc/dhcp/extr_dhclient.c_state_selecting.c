#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* time_t ;
struct interface_info {TYPE_4__* client; } ;
struct client_lease {int /*<<< orphan*/  rebind; int /*<<< orphan*/  renewal; void* expiry; TYPE_1__* options; struct client_lease* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  xid; } ;
struct TYPE_8__ {TYPE_3__ packet; int /*<<< orphan*/  xid; TYPE_2__* config; int /*<<< orphan*/  interval; void* first_sending; void* state; int /*<<< orphan*/  destination; struct client_lease* new; struct client_lease* offered_leases; } ;
struct TYPE_6__ {int /*<<< orphan*/  initial_interval; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t DHO_DHCP_MESSAGE_TYPE ; 
 void* S_INIT ; 
 void* S_REQUESTING ; 
 int /*<<< orphan*/  S_SELECTING ; 
 int /*<<< orphan*/  bind_lease (struct interface_info*) ; 
 int /*<<< orphan*/  cancel_timeout (void (*) (void*),struct interface_info*) ; 
 int /*<<< orphan*/  check_arp (struct interface_info*,struct client_lease*) ; 
 int /*<<< orphan*/  free_client_lease (struct client_lease*) ; 
 int /*<<< orphan*/  iaddr_broadcast ; 
 int /*<<< orphan*/  make_request (struct interface_info*,struct client_lease*) ; 
 void send_discover (void*) ; 
 int /*<<< orphan*/  send_request (struct interface_info*) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  state_init (struct interface_info*) ; 
 int /*<<< orphan*/  time (void**) ; 

void
state_selecting(void *ipp)
{
	struct interface_info *ip = ipp;
	struct client_lease *lp, *next, *picked;
        time_t cur_time;

	ASSERT_STATE(state, S_SELECTING);

        time(&cur_time);

	/* Cancel state_selecting and send_discover timeouts, since either
	   one could have got us here. */
	cancel_timeout(state_selecting, ip);
	cancel_timeout(send_discover, ip);

	/* We have received one or more DHCPOFFER packets.   Currently,
	   the only criterion by which we judge leases is whether or
	   not we get a response when we arp for them. */
	picked = NULL;
	for (lp = ip->client->offered_leases; lp; lp = next) {
		next = lp->next;

		/* Check to see if we got an ARPREPLY for the address
		   in this particular lease. */
		if (!picked) {
                    if( !check_arp(ip,lp) ) goto freeit;
                    picked = lp;
                    picked->next = NULL;
		} else {
freeit:
			free_client_lease(lp);
		}
	}
	ip->client->offered_leases = NULL;

	/* If we just tossed all the leases we were offered, go back
	   to square one. */
	if (!picked) {
		ip->client->state = S_INIT;
		state_init(ip);
		return;
	}

	/* If it was a BOOTREPLY, we can just take the address right now. */
	if (!picked->options[DHO_DHCP_MESSAGE_TYPE].len) {
		ip->client->new = picked;

		/* Make up some lease expiry times
		   XXX these should be configurable. */
		ip->client->new->expiry = cur_time + 12000;
		ip->client->new->renewal += cur_time + 8000;
		ip->client->new->rebind += cur_time + 10000;

		ip->client->state = S_REQUESTING;

		/* Bind to the address we received. */
		bind_lease(ip);
		return;
	}

	/* Go to the REQUESTING state. */
	ip->client->destination = iaddr_broadcast;
	ip->client->state = S_REQUESTING;
	ip->client->first_sending = cur_time;
	ip->client->interval = ip->client->config->initial_interval;

	/* Make a DHCPREQUEST packet from the lease we picked. */
	make_request(ip, picked);
	ip->client->xid = ip->client->packet.xid;

	/* Toss the lease we picked - we'll get it back in a DHCPACK. */
	free_client_lease(picked);

	/* Add an immediate timeout to send the first DHCPREQUEST packet. */
	send_request(ip);
}