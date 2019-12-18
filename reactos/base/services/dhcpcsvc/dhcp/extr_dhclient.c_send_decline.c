#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct interface_info {TYPE_1__* client; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  packet_length; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  inaddr_any ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_packet (struct interface_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ sockaddr_broadcast ; 

void
send_decline(void *ipp)
{
	struct interface_info *ip = ipp;

	note("DHCPDECLINE on %s to %s port %d", ip->name,
	    inet_ntoa(sockaddr_broadcast.sin_addr),
	    ntohs(sockaddr_broadcast.sin_port));

	/* Send out a packet. */
	(void) send_packet(ip, &ip->client->packet, ip->client->packet_length,
	    inaddr_any, &sockaddr_broadcast, NULL);
}