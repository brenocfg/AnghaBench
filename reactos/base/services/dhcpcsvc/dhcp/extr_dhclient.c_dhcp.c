#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packet {int packet_type; int /*<<< orphan*/  client_addr; TYPE_3__* interface; } ;
struct iaddrlist {int /*<<< orphan*/  addr; struct iaddrlist* next; } ;
struct TYPE_6__ {TYPE_2__* client; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_4__ {struct iaddrlist* reject_list; } ;

/* Variables and functions */
#define  DHCPACK 130 
#define  DHCPNAK 129 
#define  DHCPOFFER 128 
 scalar_t__ addr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void dhcpack (struct packet*) ; 
 void dhcpnak (struct packet*) ; 
 void dhcpoffer (struct packet*) ; 
 int /*<<< orphan*/  note (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  piaddr (int /*<<< orphan*/ ) ; 
 void stub1 (struct packet*) ; 

void
dhcp(struct packet *packet)
{
	struct iaddrlist *ap;
	void (*handler)(struct packet *);
	char *type;

	switch (packet->packet_type) {
	case DHCPOFFER:
		handler = dhcpoffer;
		type = "DHCPOFFER";
		break;
	case DHCPNAK:
		handler = dhcpnak;
		type = "DHCPNACK";
		break;
	case DHCPACK:
		handler = dhcpack;
		type = "DHCPACK";
		break;
	default:
		return;
	}

	/* If there's a reject list, make sure this packet's sender isn't
	   on it. */
	for (ap = packet->interface->client->config->reject_list;
	    ap; ap = ap->next) {
		if (addr_eq(packet->client_addr, ap->addr)) {
			note("%s from %s rejected.", type, piaddr(ap->addr));
			return;
		}
	}
	(*handler)(packet);
}