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
struct ipv6_opt_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  IPV6_TLV_JUMBO 129 
#define  IPV6_TLV_PAD1 128 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcf_csum_ipv6_hopopts(struct ipv6_opt_hdr *ip6xh, unsigned int ixhl,
				 unsigned int *pl)
{
	int off, len, optlen;
	unsigned char *xh = (void *)ip6xh;

	off = sizeof(*ip6xh);
	len = ixhl - off;

	while (len > 1) {
		switch (xh[off]) {
		case IPV6_TLV_PAD1:
			optlen = 1;
			break;
		case IPV6_TLV_JUMBO:
			optlen = xh[off + 1] + 2;
			if (optlen != 6 || len < 6 || (off & 3) != 2)
				/* wrong jumbo option length/alignment */
				return 0;
			*pl = ntohl(*(__be32 *)(xh + off + 2));
			goto done;
		default:
			optlen = xh[off + 1] + 2;
			if (optlen > len)
				/* ignore obscure options */
				goto done;
			break;
		}
		off += optlen;
		len -= optlen;
	}

done:
	return 1;
}