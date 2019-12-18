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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct iphdr {int ihl; int version; int protocol; int ttl; void* daddr; void* saddr; void* tot_len; scalar_t__ frag_off; } ;
struct ethhdr {void* h_proto; } ;

/* Variables and functions */
 int DATA_CHAR ; 
 int DATA_LEN ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_P_IP ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 scalar_t__ rand () ; 

__attribute__((used)) static void create_payload(void *pay, size_t *len)
{
	int i;
	struct ethhdr *eth = pay;
	struct iphdr *ip = pay + sizeof(*eth);

	/* Lets create some broken crap, that still passes
	 * our BPF filter.
	 */

	*len = DATA_LEN + 42;

	memset(pay, 0xff, ETH_ALEN * 2);
	eth->h_proto = htons(ETH_P_IP);

	for (i = 0; i < sizeof(*ip); ++i)
		((uint8_t *) pay)[i + sizeof(*eth)] = (uint8_t) rand();

	ip->ihl = 5;
	ip->version = 4;
	ip->protocol = 0x11;
	ip->frag_off = 0;
	ip->ttl = 64;
	ip->tot_len = htons((uint16_t) *len - sizeof(*eth));

	ip->saddr = htonl(INADDR_LOOPBACK);
	ip->daddr = htonl(INADDR_LOOPBACK);

	memset(pay + sizeof(*eth) + sizeof(*ip),
	       DATA_CHAR, DATA_LEN);
}