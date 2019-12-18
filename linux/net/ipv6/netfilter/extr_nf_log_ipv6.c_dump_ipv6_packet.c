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
typedef  int u_int8_t ;
struct sk_buff {int mark; int /*<<< orphan*/  sk; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {unsigned int logflags; } ;
struct TYPE_4__ {TYPE_1__ log; } ;
struct nf_loginfo {scalar_t__ type; TYPE_2__ u; } ;
struct nf_log_buf {int dummy; } ;
struct net {int dummy; } ;
struct ipv6hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ipv6_opt_hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_esp_hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_auth_hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct icmp6hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct frag_hdr {int payload_len; int nexthdr; int frag_off; int const icmp6_type; int icmp6_identifier; int icmp6_sequence; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_pointer; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  spi; int /*<<< orphan*/  identification; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  _ip6h ;
typedef  int /*<<< orphan*/  _icmp6h ;
typedef  int /*<<< orphan*/  _hdr ;
typedef  int /*<<< orphan*/  _fhdr ;
typedef  int /*<<< orphan*/  _esph ;
typedef  int /*<<< orphan*/  _ahdr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  ICMPV6_DEST_UNREACH 146 
#define  ICMPV6_ECHO_REPLY 145 
#define  ICMPV6_ECHO_REQUEST 144 
#define  ICMPV6_MGM_QUERY 143 
#define  ICMPV6_MGM_REDUCTION 142 
#define  ICMPV6_MGM_REPORT 141 
#define  ICMPV6_PARAMPROB 140 
#define  ICMPV6_PKT_TOOBIG 139 
#define  ICMPV6_TIME_EXCEED 138 
#define  IPPROTO_AH 137 
#define  IPPROTO_DSTOPTS 136 
#define  IPPROTO_ESP 135 
#define  IPPROTO_FRAGMENT 134 
#define  IPPROTO_HOPOPTS 133 
#define  IPPROTO_ICMPV6 132 
#define  IPPROTO_ROUTING 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int NEXTHDR_NONE ; 
 unsigned int NF_LOG_DEFAULT_MASK ; 
 unsigned int NF_LOG_IPOPT ; 
 scalar_t__ NF_LOG_TYPE_LOG ; 
 unsigned int NF_LOG_UID ; 
 int htons (int) ; 
 unsigned int ipv6_authlen (struct ipv6hdr const*) ; 
 unsigned int ipv6_optlen (struct ipv6hdr const*) ; 
 scalar_t__ nf_ip6_ext_hdr (int) ; 
 int /*<<< orphan*/  nf_log_buf_add (struct nf_log_buf*,char*,...) ; 
 int /*<<< orphan*/  nf_log_dump_sk_uid_gid (struct net*,struct nf_log_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_dump_tcp_header (struct nf_log_buf*,struct sk_buff const*,int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nf_log_dump_udp_header (struct nf_log_buf*,struct sk_buff const*,int,int,unsigned int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int) ; 
 struct ipv6hdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct ipv6hdr*) ; 

__attribute__((used)) static void dump_ipv6_packet(struct net *net, struct nf_log_buf *m,
			     const struct nf_loginfo *info,
			     const struct sk_buff *skb, unsigned int ip6hoff,
			     int recurse)
{
	u_int8_t currenthdr;
	int fragment;
	struct ipv6hdr _ip6h;
	const struct ipv6hdr *ih;
	unsigned int ptr;
	unsigned int hdrlen = 0;
	unsigned int logflags;

	if (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;
	else
		logflags = NF_LOG_DEFAULT_MASK;

	ih = skb_header_pointer(skb, ip6hoff, sizeof(_ip6h), &_ip6h);
	if (ih == NULL) {
		nf_log_buf_add(m, "TRUNCATED");
		return;
	}

	/* Max length: 88 "SRC=0000.0000.0000.0000.0000.0000.0000.0000 DST=0000.0000.0000.0000.0000.0000.0000.0000 " */
	nf_log_buf_add(m, "SRC=%pI6 DST=%pI6 ", &ih->saddr, &ih->daddr);

	/* Max length: 44 "LEN=65535 TC=255 HOPLIMIT=255 FLOWLBL=FFFFF " */
	nf_log_buf_add(m, "LEN=%zu TC=%u HOPLIMIT=%u FLOWLBL=%u ",
	       ntohs(ih->payload_len) + sizeof(struct ipv6hdr),
	       (ntohl(*(__be32 *)ih) & 0x0ff00000) >> 20,
	       ih->hop_limit,
	       (ntohl(*(__be32 *)ih) & 0x000fffff));

	fragment = 0;
	ptr = ip6hoff + sizeof(struct ipv6hdr);
	currenthdr = ih->nexthdr;
	while (currenthdr != NEXTHDR_NONE && nf_ip6_ext_hdr(currenthdr)) {
		struct ipv6_opt_hdr _hdr;
		const struct ipv6_opt_hdr *hp;

		hp = skb_header_pointer(skb, ptr, sizeof(_hdr), &_hdr);
		if (hp == NULL) {
			nf_log_buf_add(m, "TRUNCATED");
			return;
		}

		/* Max length: 48 "OPT (...) " */
		if (logflags & NF_LOG_IPOPT)
			nf_log_buf_add(m, "OPT ( ");

		switch (currenthdr) {
		case IPPROTO_FRAGMENT: {
			struct frag_hdr _fhdr;
			const struct frag_hdr *fh;

			nf_log_buf_add(m, "FRAG:");
			fh = skb_header_pointer(skb, ptr, sizeof(_fhdr),
						&_fhdr);
			if (fh == NULL) {
				nf_log_buf_add(m, "TRUNCATED ");
				return;
			}

			/* Max length: 6 "65535 " */
			nf_log_buf_add(m, "%u ", ntohs(fh->frag_off) & 0xFFF8);

			/* Max length: 11 "INCOMPLETE " */
			if (fh->frag_off & htons(0x0001))
				nf_log_buf_add(m, "INCOMPLETE ");

			nf_log_buf_add(m, "ID:%08x ",
				       ntohl(fh->identification));

			if (ntohs(fh->frag_off) & 0xFFF8)
				fragment = 1;

			hdrlen = 8;

			break;
		}
		case IPPROTO_DSTOPTS:
		case IPPROTO_ROUTING:
		case IPPROTO_HOPOPTS:
			if (fragment) {
				if (logflags & NF_LOG_IPOPT)
					nf_log_buf_add(m, ")");
				return;
			}
			hdrlen = ipv6_optlen(hp);
			break;
		/* Max Length */
		case IPPROTO_AH:
			if (logflags & NF_LOG_IPOPT) {
				struct ip_auth_hdr _ahdr;
				const struct ip_auth_hdr *ah;

				/* Max length: 3 "AH " */
				nf_log_buf_add(m, "AH ");

				if (fragment) {
					nf_log_buf_add(m, ")");
					return;
				}

				ah = skb_header_pointer(skb, ptr, sizeof(_ahdr),
							&_ahdr);
				if (ah == NULL) {
					/*
					 * Max length: 26 "INCOMPLETE [65535
					 *  bytes] )"
					 */
					nf_log_buf_add(m, "INCOMPLETE [%u bytes] )",
						       skb->len - ptr);
					return;
				}

				/* Length: 15 "SPI=0xF1234567 */
				nf_log_buf_add(m, "SPI=0x%x ", ntohl(ah->spi));

			}

			hdrlen = ipv6_authlen(hp);
			break;
		case IPPROTO_ESP:
			if (logflags & NF_LOG_IPOPT) {
				struct ip_esp_hdr _esph;
				const struct ip_esp_hdr *eh;

				/* Max length: 4 "ESP " */
				nf_log_buf_add(m, "ESP ");

				if (fragment) {
					nf_log_buf_add(m, ")");
					return;
				}

				/*
				 * Max length: 26 "INCOMPLETE [65535 bytes] )"
				 */
				eh = skb_header_pointer(skb, ptr, sizeof(_esph),
							&_esph);
				if (eh == NULL) {
					nf_log_buf_add(m, "INCOMPLETE [%u bytes] )",
						       skb->len - ptr);
					return;
				}

				/* Length: 16 "SPI=0xF1234567 )" */
				nf_log_buf_add(m, "SPI=0x%x )",
					       ntohl(eh->spi));
			}
			return;
		default:
			/* Max length: 20 "Unknown Ext Hdr 255" */
			nf_log_buf_add(m, "Unknown Ext Hdr %u", currenthdr);
			return;
		}
		if (logflags & NF_LOG_IPOPT)
			nf_log_buf_add(m, ") ");

		currenthdr = hp->nexthdr;
		ptr += hdrlen;
	}

	switch (currenthdr) {
	case IPPROTO_TCP:
		if (nf_log_dump_tcp_header(m, skb, currenthdr, fragment,
					   ptr, logflags))
			return;
		break;
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE:
		if (nf_log_dump_udp_header(m, skb, currenthdr, fragment, ptr))
			return;
		break;
	case IPPROTO_ICMPV6: {
		struct icmp6hdr _icmp6h;
		const struct icmp6hdr *ic;

		/* Max length: 13 "PROTO=ICMPv6 " */
		nf_log_buf_add(m, "PROTO=ICMPv6 ");

		if (fragment)
			break;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ic = skb_header_pointer(skb, ptr, sizeof(_icmp6h), &_icmp6h);
		if (ic == NULL) {
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - ptr);
			return;
		}

		/* Max length: 18 "TYPE=255 CODE=255 " */
		nf_log_buf_add(m, "TYPE=%u CODE=%u ",
			       ic->icmp6_type, ic->icmp6_code);

		switch (ic->icmp6_type) {
		case ICMPV6_ECHO_REQUEST:
		case ICMPV6_ECHO_REPLY:
			/* Max length: 19 "ID=65535 SEQ=65535 " */
			nf_log_buf_add(m, "ID=%u SEQ=%u ",
				ntohs(ic->icmp6_identifier),
				ntohs(ic->icmp6_sequence));
			break;
		case ICMPV6_MGM_QUERY:
		case ICMPV6_MGM_REPORT:
		case ICMPV6_MGM_REDUCTION:
			break;

		case ICMPV6_PARAMPROB:
			/* Max length: 17 "POINTER=ffffffff " */
			nf_log_buf_add(m, "POINTER=%08x ",
				       ntohl(ic->icmp6_pointer));
			/* Fall through */
		case ICMPV6_DEST_UNREACH:
		case ICMPV6_PKT_TOOBIG:
		case ICMPV6_TIME_EXCEED:
			/* Max length: 3+maxlen */
			if (recurse) {
				nf_log_buf_add(m, "[");
				dump_ipv6_packet(net, m, info, skb,
						 ptr + sizeof(_icmp6h), 0);
				nf_log_buf_add(m, "] ");
			}

			/* Max length: 10 "MTU=65535 " */
			if (ic->icmp6_type == ICMPV6_PKT_TOOBIG) {
				nf_log_buf_add(m, "MTU=%u ",
					       ntohl(ic->icmp6_mtu));
			}
		}
		break;
	}
	/* Max length: 10 "PROTO=255 " */
	default:
		nf_log_buf_add(m, "PROTO=%u ", currenthdr);
	}

	/* Max length: 15 "UID=4294967295 " */
	if ((logflags & NF_LOG_UID) && recurse)
		nf_log_dump_sk_uid_gid(net, m, skb->sk);

	/* Max length: 16 "MARK=0xFFFFFFFF " */
	if (recurse && skb->mark)
		nf_log_buf_add(m, "MARK=0x%x ", skb->mark);
}