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
struct synproxy_options {int tsecr; int tsval; int options; int wscale; } ;
struct nf_synproxy_info {int wscale; } ;

/* Variables and functions */
 int NF_SYNPROXY_OPT_ECN ; 
 int NF_SYNPROXY_OPT_SACK_PERM ; 
 int NF_SYNPROXY_OPT_WSCALE ; 
 int tcp_time_stamp_raw () ; 

void synproxy_init_timestamp_cookie(const struct nf_synproxy_info *info,
				    struct synproxy_options *opts)
{
	opts->tsecr = opts->tsval;
	opts->tsval = tcp_time_stamp_raw() & ~0x3f;

	if (opts->options & NF_SYNPROXY_OPT_WSCALE) {
		opts->tsval |= opts->wscale;
		opts->wscale = info->wscale;
	} else
		opts->tsval |= 0xf;

	if (opts->options & NF_SYNPROXY_OPT_SACK_PERM)
		opts->tsval |= 1 << 4;

	if (opts->options & NF_SYNPROXY_OPT_ECN)
		opts->tsval |= 1 << 5;
}