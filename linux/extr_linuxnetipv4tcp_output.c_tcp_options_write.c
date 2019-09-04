#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ dsack; } ;
struct tcp_sock {TYPE_1__ rx_opt; struct tcp_sack_block* selective_acks; struct tcp_sack_block* duplicate_sack; } ;
struct tcp_sack_block {int start_seq; int end_seq; } ;
struct tcp_out_options {int options; int mss; int tsval; int tsecr; int ws; int num_sack_blocks; struct tcp_fastopen_cookie* fastopen_cookie; int /*<<< orphan*/ * hash_location; } ;
struct tcp_fastopen_cookie {int len; int /*<<< orphan*/  val; scalar_t__ exp; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __be32 ;

/* Variables and functions */
 int OPTION_FAST_OPEN_COOKIE ; 
 int OPTION_MD5 ; 
 int OPTION_SACK_ADVERTISE ; 
 int OPTION_TS ; 
 int OPTION_WSCALE ; 
 int TCPOLEN_EXP_FASTOPEN_BASE ; 
 int TCPOLEN_FASTOPEN_BASE ; 
 int TCPOLEN_MD5SIG ; 
 int TCPOLEN_MSS ; 
 int TCPOLEN_SACK_BASE ; 
 int TCPOLEN_SACK_PERBLOCK ; 
 int TCPOLEN_SACK_PERM ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
 int TCPOPT_EXP ; 
 int /*<<< orphan*/  TCPOPT_FASTOPEN ; 
 int TCPOPT_FASTOPEN_MAGIC ; 
 int TCPOPT_MD5SIG ; 
 int TCPOPT_MSS ; 
 int TCPOPT_NOP ; 
 int TCPOPT_SACK ; 
 int TCPOPT_SACK_PERM ; 
 int TCPOPT_TIMESTAMP ; 
 int TCPOPT_WINDOW ; 
 void* htonl (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_options_write (void**,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tcp_options_write(__be32 *ptr, struct tcp_sock *tp,
			      struct tcp_out_options *opts)
{
	u16 options = opts->options;	/* mungable copy */

	if (unlikely(OPTION_MD5 & options)) {
		*ptr++ = htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
			       (TCPOPT_MD5SIG << 8) | TCPOLEN_MD5SIG);
		/* overload cookie hash location */
		opts->hash_location = (__u8 *)ptr;
		ptr += 4;
	}

	if (unlikely(opts->mss)) {
		*ptr++ = htonl((TCPOPT_MSS << 24) |
			       (TCPOLEN_MSS << 16) |
			       opts->mss);
	}

	if (likely(OPTION_TS & options)) {
		if (unlikely(OPTION_SACK_ADVERTISE & options)) {
			*ptr++ = htonl((TCPOPT_SACK_PERM << 24) |
				       (TCPOLEN_SACK_PERM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
			options &= ~OPTION_SACK_ADVERTISE;
		} else {
			*ptr++ = htonl((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		}
		*ptr++ = htonl(opts->tsval);
		*ptr++ = htonl(opts->tsecr);
	}

	if (unlikely(OPTION_SACK_ADVERTISE & options)) {
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PERM << 8) |
			       TCPOLEN_SACK_PERM);
	}

	if (unlikely(OPTION_WSCALE & options)) {
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOLEN_WINDOW << 8) |
			       opts->ws);
	}

	if (unlikely(opts->num_sack_blocks)) {
		struct tcp_sack_block *sp = tp->rx_opt.dsack ?
			tp->duplicate_sack : tp->selective_acks;
		int this_sack;

		*ptr++ = htonl((TCPOPT_NOP  << 24) |
			       (TCPOPT_NOP  << 16) |
			       (TCPOPT_SACK <<  8) |
			       (TCPOLEN_SACK_BASE + (opts->num_sack_blocks *
						     TCPOLEN_SACK_PERBLOCK)));

		for (this_sack = 0; this_sack < opts->num_sack_blocks;
		     ++this_sack) {
			*ptr++ = htonl(sp[this_sack].start_seq);
			*ptr++ = htonl(sp[this_sack].end_seq);
		}

		tp->rx_opt.dsack = 0;
	}

	if (unlikely(OPTION_FAST_OPEN_COOKIE & options)) {
		struct tcp_fastopen_cookie *foc = opts->fastopen_cookie;
		u8 *p = (u8 *)ptr;
		u32 len; /* Fast Open option length */

		if (foc->exp) {
			len = TCPOLEN_EXP_FASTOPEN_BASE + foc->len;
			*ptr = htonl((TCPOPT_EXP << 24) | (len << 16) |
				     TCPOPT_FASTOPEN_MAGIC);
			p += TCPOLEN_EXP_FASTOPEN_BASE;
		} else {
			len = TCPOLEN_FASTOPEN_BASE + foc->len;
			*p++ = TCPOPT_FASTOPEN;
			*p++ = len;
		}

		memcpy(p, foc->val, foc->len);
		if ((len & 3) == 2) {
			p[foc->len] = TCPOPT_NOP;
			p[foc->len + 1] = TCPOPT_NOP;
		}
		ptr += (len + 3) >> 2;
	}

	smc_options_write(ptr, &options);
}