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
typedef  int time_t ;
struct packet {int /*<<< orphan*/  client_addr; TYPE_2__* raw; struct interface_info* interface; } ;
struct TYPE_5__ {scalar_t__ hlen; int /*<<< orphan*/  haddr; } ;
struct interface_info {TYPE_4__* client; TYPE_1__ hw_address; } ;
struct client_lease {int expiry; int renewal; int rebind; int obtained; TYPE_3__* options; } ;
struct TYPE_8__ {scalar_t__ xid; scalar_t__ state; struct client_lease* new; } ;
struct TYPE_7__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_6__ {scalar_t__ xid; scalar_t__ hlen; int /*<<< orphan*/  chaddr; } ;

/* Variables and functions */
 int DHCP_DEFAULT_LEASE_TIME ; 
 size_t DHO_DHCP_LEASE_TIME ; 
 size_t DHO_DHCP_REBINDING_TIME ; 
 size_t DHO_DHCP_RENEWAL_TIME ; 
 scalar_t__ S_REBINDING ; 
 scalar_t__ S_REBOOTING ; 
 scalar_t__ S_RENEWING ; 
 scalar_t__ S_REQUESTING ; 
 void* TIME_MAX ; 
 int /*<<< orphan*/  bind_lease (struct interface_info*) ; 
 int /*<<< orphan*/  cancel_timeout (int /*<<< orphan*/ ,struct interface_info*) ; 
 void* getULong (scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  note (char*,...) ; 
 struct client_lease* packet_to_lease (struct packet*) ; 
 int /*<<< orphan*/  piaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request ; 
 int /*<<< orphan*/  time (int*) ; 

void
dhcpack(struct packet *packet)
{
	struct interface_info *ip = packet->interface;
	struct client_lease *lease;
        time_t cur_time;

        time(&cur_time);

	/* If we're not receptive to an offer right now, or if the offer
	   has an unrecognizable transaction id, then just drop it. */
	if (packet->interface->client->xid != packet->raw->xid ||
	    (packet->interface->hw_address.hlen != packet->raw->hlen) ||
	    (memcmp(packet->interface->hw_address.haddr,
	    packet->raw->chaddr, packet->raw->hlen)))
		return;

	if (ip->client->state != S_REBOOTING &&
	    ip->client->state != S_REQUESTING &&
	    ip->client->state != S_RENEWING &&
	    ip->client->state != S_REBINDING)
		return;

	note("DHCPACK from %s", piaddr(packet->client_addr));

	lease = packet_to_lease(packet);
	if (!lease) {
		note("packet_to_lease failed.");
		return;
	}

	ip->client->new = lease;

	/* Stop resending DHCPREQUEST. */
	cancel_timeout(send_request, ip);

	/* Figure out the lease time. */
	if (ip->client->new->options[DHO_DHCP_LEASE_TIME].data)
		ip->client->new->expiry = getULong(
		    ip->client->new->options[DHO_DHCP_LEASE_TIME].data);
	else
		ip->client->new->expiry = DHCP_DEFAULT_LEASE_TIME;
	/* A number that looks negative here is really just very large,
	   because the lease expiry offset is unsigned. */
	if (ip->client->new->expiry < 0)
		ip->client->new->expiry = TIME_MAX;
	/* XXX should be fixed by resetting the client state */
	if (ip->client->new->expiry < 60)
		ip->client->new->expiry = 60;

	/* Take the server-provided renewal time if there is one;
	   otherwise figure it out according to the spec. */
	if (ip->client->new->options[DHO_DHCP_RENEWAL_TIME].len)
		ip->client->new->renewal = getULong(
		    ip->client->new->options[DHO_DHCP_RENEWAL_TIME].data);
	else
		ip->client->new->renewal = ip->client->new->expiry / 2;

	/* Same deal with the rebind time. */
	if (ip->client->new->options[DHO_DHCP_REBINDING_TIME].len)
		ip->client->new->rebind = getULong(
		    ip->client->new->options[DHO_DHCP_REBINDING_TIME].data);
	else
		ip->client->new->rebind = ip->client->new->renewal +
		    ip->client->new->renewal / 2 + ip->client->new->renewal / 4;

#ifdef __REACTOS__
	ip->client->new->obtained = cur_time;
#endif
	ip->client->new->expiry += cur_time;
	/* Lease lengths can never be negative. */
	if (ip->client->new->expiry < cur_time)
		ip->client->new->expiry = TIME_MAX;
	ip->client->new->renewal += cur_time;
	if (ip->client->new->renewal < cur_time)
		ip->client->new->renewal = TIME_MAX;
	ip->client->new->rebind += cur_time;
	if (ip->client->new->rebind < cur_time)
		ip->client->new->rebind = TIME_MAX;

	bind_lease(ip);
}