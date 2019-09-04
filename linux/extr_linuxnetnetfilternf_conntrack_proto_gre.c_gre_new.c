#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {unsigned int stream_timeout; unsigned int timeout; } ;
struct TYPE_6__ {TYPE_2__ gre; } ;
struct nf_conn {TYPE_3__ proto; TYPE_1__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 size_t GRE_CT_REPLIED ; 
 size_t GRE_CT_UNREPLIED ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 unsigned int* gre_get_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool gre_new(struct nf_conn *ct, const struct sk_buff *skb,
		    unsigned int dataoff)
{
	unsigned int *timeouts = nf_ct_timeout_lookup(ct);

	if (!timeouts)
		timeouts = gre_get_timeouts(nf_ct_net(ct));

	pr_debug(": ");
	nf_ct_dump_tuple(&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);

	/* initialize to sane value.  Ideally a conntrack helper
	 * (e.g. in case of pptp) is increasing them */
	ct->proto.gre.stream_timeout = timeouts[GRE_CT_REPLIED];
	ct->proto.gre.timeout = timeouts[GRE_CT_UNREPLIED];

	return true;
}