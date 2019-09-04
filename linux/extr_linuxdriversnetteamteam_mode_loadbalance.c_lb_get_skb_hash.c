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
typedef  int /*<<< orphan*/  uint32_t ;
struct sk_buff {int dummy; } ;
struct lb_priv {int /*<<< orphan*/  fp; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_RUN (struct bpf_prog*,struct sk_buff*) ; 
 struct bpf_prog* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int lb_get_skb_hash(struct lb_priv *lb_priv,
				    struct sk_buff *skb)
{
	struct bpf_prog *fp;
	uint32_t lhash;
	unsigned char *c;

	fp = rcu_dereference_bh(lb_priv->fp);
	if (unlikely(!fp))
		return 0;
	lhash = BPF_PROG_RUN(fp, skb);
	c = (char *) &lhash;
	return c[0] ^ c[1] ^ c[2] ^ c[3];
}