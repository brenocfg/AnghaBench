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
struct flow_dissector_key_enc_opts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_OPTS ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_OPTS_MASK ; 
 int fl_dump_key_options (struct sk_buff*,int /*<<< orphan*/ ,struct flow_dissector_key_enc_opts*) ; 

__attribute__((used)) static int fl_dump_key_enc_opt(struct sk_buff *skb,
			       struct flow_dissector_key_enc_opts *key_opts,
			       struct flow_dissector_key_enc_opts *msk_opts)
{
	int err;

	err = fl_dump_key_options(skb, TCA_FLOWER_KEY_ENC_OPTS, key_opts);
	if (err)
		return err;

	return fl_dump_key_options(skb, TCA_FLOWER_KEY_ENC_OPTS_MASK, msk_opts);
}