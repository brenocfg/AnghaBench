#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int len; } ;
struct TYPE_4__ {scalar_t__ magic; int nid; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int ether_type; int /*<<< orphan*/  ether_dhost; } ;
struct ead_packet {scalar_t__ proto; int destport; TYPE_2__ msg; TYPE_1__ eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAD_MAGIC ; 
 int /*<<< orphan*/  EAD_PORT ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 scalar_t__ UIP_PROTO_UDP ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nid ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_message (struct ead_packet*,scalar_t__) ; 

__attribute__((used)) static void
handle_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes)
{
	struct ead_packet *pkt = (struct ead_packet *) bytes;

	if (h->len < sizeof(struct ead_packet))
		return;

	if (pkt->eh.ether_type != htons(ETHERTYPE_IP))
		return;

	if (memcmp(pkt->eh.ether_dhost, "\xff\xff\xff\xff\xff\xff", 6) != 0)
		return;

	if (pkt->proto != UIP_PROTO_UDP)
		return;

	if (pkt->destport != htons(EAD_PORT))
		return;

	if (pkt->msg.magic != htonl(EAD_MAGIC))
		return;

	if (h->len < sizeof(struct ead_packet) + ntohl(pkt->msg.len))
		return;

	if ((pkt->msg.nid != 0xffff) &&
		(pkt->msg.nid != htons(nid)))
		return;

	parse_message(pkt, h->len);
}