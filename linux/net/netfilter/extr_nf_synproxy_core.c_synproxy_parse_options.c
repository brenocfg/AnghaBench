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
typedef  int /*<<< orphan*/  u8 ;
struct tcphdr {int doff; } ;
struct synproxy_options {scalar_t__ options; void* tsecr; void* tsval; int /*<<< orphan*/  wscale; int /*<<< orphan*/  mss_option; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ NF_SYNPROXY_OPT_MSS ; 
 scalar_t__ NF_SYNPROXY_OPT_SACK_PERM ; 
 scalar_t__ NF_SYNPROXY_OPT_TIMESTAMP ; 
 scalar_t__ NF_SYNPROXY_OPT_WSCALE ; 
 int TCPOLEN_MSS ; 
 int TCPOLEN_SACK_PERM ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
#define  TCPOPT_EOL 133 
#define  TCPOPT_MSS 132 
#define  TCPOPT_NOP 131 
#define  TCPOPT_SACK_PERM 130 
#define  TCPOPT_TIMESTAMP 129 
#define  TCPOPT_WINDOW 128 
 int /*<<< orphan*/  TCP_MAX_WSCALE ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 void* get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff const*,unsigned int,int,int /*<<< orphan*/ *) ; 

bool
synproxy_parse_options(const struct sk_buff *skb, unsigned int doff,
		       const struct tcphdr *th, struct synproxy_options *opts)
{
	int length = (th->doff * 4) - sizeof(*th);
	u8 buf[40], *ptr;

	ptr = skb_header_pointer(skb, doff + sizeof(*th), length, buf);
	if (ptr == NULL)
		return false;

	opts->options = 0;
	while (length > 0) {
		int opcode = *ptr++;
		int opsize;

		switch (opcode) {
		case TCPOPT_EOL:
			return true;
		case TCPOPT_NOP:
			length--;
			continue;
		default:
			opsize = *ptr++;
			if (opsize < 2)
				return true;
			if (opsize > length)
				return true;

			switch (opcode) {
			case TCPOPT_MSS:
				if (opsize == TCPOLEN_MSS) {
					opts->mss_option = get_unaligned_be16(ptr);
					opts->options |= NF_SYNPROXY_OPT_MSS;
				}
				break;
			case TCPOPT_WINDOW:
				if (opsize == TCPOLEN_WINDOW) {
					opts->wscale = *ptr;
					if (opts->wscale > TCP_MAX_WSCALE)
						opts->wscale = TCP_MAX_WSCALE;
					opts->options |= NF_SYNPROXY_OPT_WSCALE;
				}
				break;
			case TCPOPT_TIMESTAMP:
				if (opsize == TCPOLEN_TIMESTAMP) {
					opts->tsval = get_unaligned_be32(ptr);
					opts->tsecr = get_unaligned_be32(ptr + 4);
					opts->options |= NF_SYNPROXY_OPT_TIMESTAMP;
				}
				break;
			case TCPOPT_SACK_PERM:
				if (opsize == TCPOLEN_SACK_PERM)
					opts->options |= NF_SYNPROXY_OPT_SACK_PERM;
				break;
			}

			ptr += opsize - 2;
			length -= opsize;
		}
	}
	return true;
}