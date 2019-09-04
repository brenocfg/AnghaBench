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
struct synproxy_options {int options; } ;

/* Variables and functions */
 scalar_t__ TCPOLEN_MSS_ALIGNED ; 
 scalar_t__ TCPOLEN_SACKPERM_ALIGNED ; 
 scalar_t__ TCPOLEN_TSTAMP_ALIGNED ; 
 scalar_t__ TCPOLEN_WSCALE_ALIGNED ; 
 int XT_SYNPROXY_OPT_MSS ; 
 int XT_SYNPROXY_OPT_SACK_PERM ; 
 int XT_SYNPROXY_OPT_TIMESTAMP ; 
 int XT_SYNPROXY_OPT_WSCALE ; 

unsigned int synproxy_options_size(const struct synproxy_options *opts)
{
	unsigned int size = 0;

	if (opts->options & XT_SYNPROXY_OPT_MSS)
		size += TCPOLEN_MSS_ALIGNED;
	if (opts->options & XT_SYNPROXY_OPT_TIMESTAMP)
		size += TCPOLEN_TSTAMP_ALIGNED;
	else if (opts->options & XT_SYNPROXY_OPT_SACK_PERM)
		size += TCPOLEN_SACKPERM_ALIGNED;
	if (opts->options & XT_SYNPROXY_OPT_WSCALE)
		size += TCPOLEN_WSCALE_ALIGNED;

	return size;
}