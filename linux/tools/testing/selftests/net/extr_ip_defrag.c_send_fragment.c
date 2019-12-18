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
typedef  int /*<<< orphan*/  uint8_t ;
struct udphdr {scalar_t__ check; void* len; void* dest; void* source; } ;
struct sockaddr {int dummy; } ;
struct ip6_hdr {void* ip6_plen; } ;
struct ip6_frag {void* ip6f_offlg; } ;
struct ip {void* ip_len; void* ip_off; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int FRAG_HLEN ; 
 int IP4_HLEN ; 
 int IP4_MF ; 
 int IP6_HLEN ; 
 int IP6_MF ; 
 int UDP_HLEN ; 
 int cfg_port ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  frag_counter ; 
 void* htons (int) ; 
 int /*<<< orphan*/ * ip_frame ; 
 int max_frag_len ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct udphdr*,int) ; 
 int payload_len ; 
 int sendto (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ udp6_checksum (struct ip6_hdr*,struct udphdr*) ; 
 scalar_t__ udp_checksum (struct ip*,struct udphdr*) ; 
 struct udphdr* udp_payload ; 

__attribute__((used)) static void send_fragment(int fd_raw, struct sockaddr *addr, socklen_t alen,
				int offset, bool ipv6)
{
	int frag_len;
	int res;
	int payload_offset = offset > 0 ? offset - UDP_HLEN : 0;
	uint8_t *frag_start = ipv6 ? ip_frame + IP6_HLEN + FRAG_HLEN :
					ip_frame + IP4_HLEN;

	if (offset == 0) {
		struct udphdr udphdr;
		udphdr.source = htons(cfg_port + 1);
		udphdr.dest = htons(cfg_port);
		udphdr.len = htons(UDP_HLEN + payload_len);
		udphdr.check = 0;
		if (ipv6)
			udphdr.check = udp6_checksum((struct ip6_hdr *)ip_frame, &udphdr);
		else
			udphdr.check = udp_checksum((struct ip *)ip_frame, &udphdr);
		memcpy(frag_start, &udphdr, UDP_HLEN);
	}

	if (ipv6) {
		struct ip6_hdr *ip6hdr = (struct ip6_hdr *)ip_frame;
		struct ip6_frag *fraghdr = (struct ip6_frag *)(ip_frame + IP6_HLEN);
		if (payload_len - payload_offset <= max_frag_len && offset > 0) {
			/* This is the last fragment. */
			frag_len = FRAG_HLEN + payload_len - payload_offset;
			fraghdr->ip6f_offlg = htons(offset);
		} else {
			frag_len = FRAG_HLEN + max_frag_len;
			fraghdr->ip6f_offlg = htons(offset | IP6_MF);
		}
		ip6hdr->ip6_plen = htons(frag_len);
		if (offset == 0)
			memcpy(frag_start + UDP_HLEN, udp_payload,
				frag_len - FRAG_HLEN - UDP_HLEN);
		else
			memcpy(frag_start, udp_payload + payload_offset,
				frag_len - FRAG_HLEN);
		frag_len += IP6_HLEN;
	} else {
		struct ip *iphdr = (struct ip *)ip_frame;
		if (payload_len - payload_offset <= max_frag_len && offset > 0) {
			/* This is the last fragment. */
			frag_len = IP4_HLEN + payload_len - payload_offset;
			iphdr->ip_off = htons(offset / 8);
		} else {
			frag_len = IP4_HLEN + max_frag_len;
			iphdr->ip_off = htons(offset / 8 | IP4_MF);
		}
		iphdr->ip_len = htons(frag_len);
		if (offset == 0)
			memcpy(frag_start + UDP_HLEN, udp_payload,
				frag_len - IP4_HLEN - UDP_HLEN);
		else
			memcpy(frag_start, udp_payload + payload_offset,
				frag_len - IP4_HLEN);
	}

	res = sendto(fd_raw, ip_frame, frag_len, 0, addr, alen);
	if (res < 0)
		error(1, errno, "send_fragment");
	if (res != frag_len)
		error(1, 0, "send_fragment: %d vs %d", res, frag_len);

	frag_counter++;
}