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
struct nlattr {int dummy; } ;
struct flow_dissector_key_enc_opts {int dst_opt_type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EMSGSIZE ; 
#define  TUNNEL_GENEVE_OPT 128 
 int fl_dump_key_geneve_opt (struct sk_buff*,struct flow_dissector_key_enc_opts*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 

__attribute__((used)) static int fl_dump_key_options(struct sk_buff *skb, int enc_opt_type,
			       struct flow_dissector_key_enc_opts *enc_opts)
{
	struct nlattr *nest;
	int err;

	if (!enc_opts->len)
		return 0;

	nest = nla_nest_start_noflag(skb, enc_opt_type);
	if (!nest)
		goto nla_put_failure;

	switch (enc_opts->dst_opt_type) {
	case TUNNEL_GENEVE_OPT:
		err = fl_dump_key_geneve_opt(skb, enc_opts);
		if (err)
			goto nla_put_failure;
		break;
	default:
		goto nla_put_failure;
	}
	nla_nest_end(skb, nest);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -EMSGSIZE;
}