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
struct tcphdr {int dummy; } ;
struct synproxy_options {int options; int mss_option; int tsval; int tsecr; int wscale; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NF_SYNPROXY_OPT_MSS ; 
 int NF_SYNPROXY_OPT_SACK_PERM ; 
 int NF_SYNPROXY_OPT_TIMESTAMP ; 
 int NF_SYNPROXY_OPT_WSCALE ; 
 int TCPOLEN_MSS ; 
 int TCPOLEN_SACK_PERM ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
 int TCPOPT_MSS ; 
 int TCPOPT_NOP ; 
 int TCPOPT_SACK_PERM ; 
 int TCPOPT_TIMESTAMP ; 
 int TCPOPT_WINDOW ; 
 void* htonl (int) ; 

__attribute__((used)) static void
synproxy_build_options(struct tcphdr *th, const struct synproxy_options *opts)
{
	__be32 *ptr = (__be32 *)(th + 1);
	u8 options = opts->options;

	if (options & NF_SYNPROXY_OPT_MSS)
		*ptr++ = htonl((TCPOPT_MSS << 24) |
			       (TCPOLEN_MSS << 16) |
			       opts->mss_option);

	if (options & NF_SYNPROXY_OPT_TIMESTAMP) {
		if (options & NF_SYNPROXY_OPT_SACK_PERM)
			*ptr++ = htonl((TCPOPT_SACK_PERM << 24) |
				       (TCPOLEN_SACK_PERM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		else
			*ptr++ = htonl((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);

		*ptr++ = htonl(opts->tsval);
		*ptr++ = htonl(opts->tsecr);
	} else if (options & NF_SYNPROXY_OPT_SACK_PERM)
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PERM << 8) |
			       TCPOLEN_SACK_PERM);

	if (options & NF_SYNPROXY_OPT_WSCALE)
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOLEN_WINDOW << 8) |
			       opts->wscale);
}