#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct TYPE_17__ {struct in_addr s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_8__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct interface_info {TYPE_5__* client; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  destination ;
struct TYPE_16__ {void* secs; } ;
struct TYPE_15__ {scalar_t__ NteContext; } ;
struct TYPE_11__ {int /*<<< orphan*/  iabuf; } ;
struct TYPE_14__ {scalar_t__ first_sending; scalar_t__ state; int interval; int /*<<< orphan*/  packet_length; TYPE_7__ packet; void* secs; TYPE_4__* active; TYPE_2__ destination; TYPE_1__* config; scalar_t__ medium; } ;
struct TYPE_12__ {int /*<<< orphan*/  iabuf; } ;
struct TYPE_13__ {scalar_t__ expiry; scalar_t__ rebind; TYPE_3__ address; scalar_t__ medium; } ;
struct TYPE_10__ {int reboot_timeout; int initial_interval; int backoff_cutoff; } ;
typedef  TYPE_6__* PDHCP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 TYPE_6__* AdapterFindInfo (struct interface_info*) ; 
 int /*<<< orphan*/  DeleteIPAddress (scalar_t__) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 struct in_addr INADDR_BROADCAST ; 
 int REMOTE_PORT ; 
 void* S_INIT ; 
 scalar_t__ S_REBOOTING ; 
 scalar_t__ S_REQUESTING ; 
 int /*<<< orphan*/  add_timeout (scalar_t__,void (*) (void*),struct interface_info*) ; 
 int /*<<< orphan*/  cancel_timeout (void (*) (void*),struct interface_info*) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_8__) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  note (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 int rand () ; 
 int /*<<< orphan*/  send_packet (struct interface_info*,TYPE_7__*,int /*<<< orphan*/ ,struct in_addr,struct sockaddr_in*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_init (struct interface_info*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

void
send_request(void *ipp)
{
	struct interface_info *ip = ipp;
	struct sockaddr_in destination;
	struct in_addr from;
	int interval;
        time_t cur_time;

        time(&cur_time); 

	/* Figure out how long it's been since we started transmitting. */
	interval = cur_time - ip->client->first_sending;

	/* If we're in the INIT-REBOOT or REQUESTING state and we're
	   past the reboot timeout, go to INIT and see if we can
	   DISCOVER an address... */
	/* XXX In the INIT-REBOOT state, if we don't get an ACK, it
	   means either that we're on a network with no DHCP server,
	   or that our server is down.  In the latter case, assuming
	   that there is a backup DHCP server, DHCPDISCOVER will get
	   us a new address, but we could also have successfully
	   reused our old address.  In the former case, we're hosed
	   anyway.  This is not a win-prone situation. */
	if ((ip->client->state == S_REBOOTING ||
	    ip->client->state == S_REQUESTING) &&
	    interval > ip->client->config->reboot_timeout) {
		ip->client->state = S_INIT;
		cancel_timeout(send_request, ip);
		state_init(ip);
		return;
	}

	/* If we're in the reboot state, make sure the media is set up
	   correctly. */
	if (ip->client->state == S_REBOOTING &&
	    !ip->client->medium &&
	    ip->client->active->medium ) {
		/* If the medium we chose won't fly, go to INIT state. */
                /* XXX Nothing for now */

		/* Record the medium. */
		ip->client->medium = ip->client->active->medium;
	}

	/* If the lease has expired, relinquish the address and go back
	   to the INIT state. */
	if (ip->client->state != S_REQUESTING &&
	    cur_time > ip->client->active->expiry) {
            PDHCP_ADAPTER Adapter = AdapterFindInfo( ip );
            /* Run the client script with the new parameters. */
            /* No script actions necessary in the expiry case */
            /* Now do a preinit on the interface so that we can
               discover a new address. */

            if( Adapter )
            {
                DeleteIPAddress( Adapter->NteContext );
                Adapter->NteContext = 0;
            }

            ip->client->state = S_INIT;
            state_init(ip);
            return;
	}

	/* Do the exponential backoff... */
	if (!ip->client->interval)
		ip->client->interval = ip->client->config->initial_interval;
	else
		ip->client->interval += ((rand() >> 2) %
		    (2 * ip->client->interval));

	/* Don't backoff past cutoff. */
	if (ip->client->interval >
	    ip->client->config->backoff_cutoff)
		ip->client->interval =
		    ((ip->client->config->backoff_cutoff / 2) +
		    ((rand() >> 2) % ip->client->interval));

	/* If the backoff would take us to the expiry time, just set the
	   timeout to the expiry time. */
	if (ip->client->state != S_REQUESTING &&
	    cur_time + ip->client->interval >
	    ip->client->active->expiry)
		ip->client->interval =
		    ip->client->active->expiry - cur_time + 1;

	/* If the lease T2 time has elapsed, or if we're not yet bound,
	   broadcast the DHCPREQUEST rather than unicasting. */
	memset(&destination, 0, sizeof(destination));
	if (ip->client->state == S_REQUESTING ||
	    ip->client->state == S_REBOOTING ||
	    cur_time > ip->client->active->rebind)
		destination.sin_addr.s_addr = INADDR_BROADCAST;
	else
		memcpy(&destination.sin_addr.s_addr,
		    ip->client->destination.iabuf,
		    sizeof(destination.sin_addr.s_addr));
	destination.sin_port = htons(REMOTE_PORT);
	destination.sin_family = AF_INET;
//	destination.sin_len = sizeof(destination);

	if (ip->client->state != S_REQUESTING)
		memcpy(&from, ip->client->active->address.iabuf,
		    sizeof(from));
	else
		from.s_addr = INADDR_ANY;

	/* Record the number of seconds since we started sending. */
	if (ip->client->state == S_REQUESTING)
		ip->client->packet.secs = ip->client->secs;
	else {
		if (interval < 65536)
			ip->client->packet.secs = htons(interval);
		else
			ip->client->packet.secs = htons(65535);
	}

	note("DHCPREQUEST on %s to %s port %d", ip->name,
	    inet_ntoa(destination.sin_addr), ntohs(destination.sin_port));

	/* Send out a packet. */
	(void) send_packet(ip, &ip->client->packet, ip->client->packet_length,
	    from, &destination, NULL);

	add_timeout(cur_time + ip->client->interval, send_request, ip);
}