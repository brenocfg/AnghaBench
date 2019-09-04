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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_protonum (struct nf_conn*) ; 
 int nf_generic_should_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool generic_new(struct nf_conn *ct, const struct sk_buff *skb,
			unsigned int dataoff)
{
	bool ret;

	ret = nf_generic_should_process(nf_ct_protonum(ct));
	if (!ret)
		pr_warn_once("conntrack: generic helper won't handle protocol %d. Please consider loading the specific helper module.\n",
			     nf_ct_protonum(ct));
	return ret;
}