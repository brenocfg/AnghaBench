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
typedef  char u8 ;
struct seg6_hmac_info {int /*<<< orphan*/  hmackeyid; } ;
struct ipv6_sr_hdr {int first_segment; char* segments; int /*<<< orphan*/  flags; } ;
typedef  char in6_addr ;
typedef  char __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int SEG6_HMAC_FIELD_LEN ; 
 int SEG6_HMAC_MAX_DIGESTSIZE ; 
 int SEG6_HMAC_RING_SIZE ; 
 int __do_hmac (struct seg6_hmac_info*,char*,int,char*,int) ; 
 char cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmac_ring ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* this_cpu_ptr (int /*<<< orphan*/ ) ; 

int seg6_hmac_compute(struct seg6_hmac_info *hinfo, struct ipv6_sr_hdr *hdr,
		      struct in6_addr *saddr, u8 *output)
{
	__be32 hmackeyid = cpu_to_be32(hinfo->hmackeyid);
	u8 tmp_out[SEG6_HMAC_MAX_DIGESTSIZE];
	int plen, i, dgsize, wrsize;
	char *ring, *off;

	/* a 160-byte buffer for digest output allows to store highest known
	 * hash function (RadioGatun) with up to 1216 bits
	 */

	/* saddr(16) + first_seg(1) + flags(1) + keyid(4) + seglist(16n) */
	plen = 16 + 1 + 1 + 4 + (hdr->first_segment + 1) * 16;

	/* this limit allows for 14 segments */
	if (plen >= SEG6_HMAC_RING_SIZE)
		return -EMSGSIZE;

	/* Let's build the HMAC text on the ring buffer. The text is composed
	 * as follows, in order:
	 *
	 * 1. Source IPv6 address (128 bits)
	 * 2. first_segment value (8 bits)
	 * 3. Flags (8 bits)
	 * 4. HMAC Key ID (32 bits)
	 * 5. All segments in the segments list (n * 128 bits)
	 */

	local_bh_disable();
	ring = this_cpu_ptr(hmac_ring);
	off = ring;

	/* source address */
	memcpy(off, saddr, 16);
	off += 16;

	/* first_segment value */
	*off++ = hdr->first_segment;

	/* flags */
	*off++ = hdr->flags;

	/* HMAC Key ID */
	memcpy(off, &hmackeyid, 4);
	off += 4;

	/* all segments in the list */
	for (i = 0; i < hdr->first_segment + 1; i++) {
		memcpy(off, hdr->segments + i, 16);
		off += 16;
	}

	dgsize = __do_hmac(hinfo, ring, plen, tmp_out,
			   SEG6_HMAC_MAX_DIGESTSIZE);
	local_bh_enable();

	if (dgsize < 0)
		return dgsize;

	wrsize = SEG6_HMAC_FIELD_LEN;
	if (wrsize > dgsize)
		wrsize = dgsize;

	memset(output, 0, SEG6_HMAC_FIELD_LEN);
	memcpy(output, tmp_out, wrsize);

	return 0;
}