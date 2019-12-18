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
struct bpf_lwt_prog {scalar_t__ name; int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  LWT_BPF_PROG_NAME ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bpf_fill_lwt_prog(struct sk_buff *skb, int attr,
			     struct bpf_lwt_prog *prog)
{
	struct nlattr *nest;

	if (!prog->prog)
		return 0;

	nest = nla_nest_start_noflag(skb, attr);
	if (!nest)
		return -EMSGSIZE;

	if (prog->name &&
	    nla_put_string(skb, LWT_BPF_PROG_NAME, prog->name))
		return -EMSGSIZE;

	return nla_nest_end(skb, nest);
}