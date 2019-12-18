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
typedef  int u8 ;
struct ipv6_opt_hdr {int dummy; } ;

/* Variables and functions */
#define  IPV6_TLV_PAD1 128 
 int ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool zero_out_mutable_opts(struct ipv6_opt_hdr *opthdr)
{
	u8 *opt = (u8 *)opthdr;
	int len = ipv6_optlen(opthdr);
	int off = 0;
	int optlen = 0;

	off += 2;
	len -= 2;

	while (len > 0) {

		switch (opt[off]) {

		case IPV6_TLV_PAD1:
			optlen = 1;
			break;
		default:
			if (len < 2)
				goto bad;
			optlen = opt[off+1]+2;
			if (len < optlen)
				goto bad;
			if (opt[off] & 0x20)
				memset(&opt[off+2], 0, opt[off+1]);
			break;
		}

		off += optlen;
		len -= optlen;
	}
	if (len == 0)
		return true;

bad:
	return false;
}