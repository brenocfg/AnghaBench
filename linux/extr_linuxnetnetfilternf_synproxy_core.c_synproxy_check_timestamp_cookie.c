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
struct synproxy_options {int wscale; int tsecr; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  XT_SYNPROXY_OPT_ECN ; 
 int /*<<< orphan*/  XT_SYNPROXY_OPT_SACK_PERM ; 
 int /*<<< orphan*/  XT_SYNPROXY_OPT_WSCALE ; 

void synproxy_check_timestamp_cookie(struct synproxy_options *opts)
{
	opts->wscale = opts->tsecr & 0xf;
	if (opts->wscale != 0xf)
		opts->options |= XT_SYNPROXY_OPT_WSCALE;

	opts->options |= opts->tsecr & (1 << 4) ? XT_SYNPROXY_OPT_SACK_PERM : 0;

	opts->options |= opts->tsecr & (1 << 5) ? XT_SYNPROXY_OPT_ECN : 0;
}