#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct seg6_local_lwt {TYPE_1__* desc; int /*<<< orphan*/  action; } ;
struct seg6_action_param {int (* put ) (struct sk_buff*,struct seg6_local_lwt*) ;} ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_2__ {int attrs; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  SEG6_LOCAL_ACTION ; 
 int SEG6_LOCAL_MAX ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct seg6_action_param* seg6_action_params ; 
 struct seg6_local_lwt* seg6_local_lwtunnel (struct lwtunnel_state*) ; 
 int stub1 (struct sk_buff*,struct seg6_local_lwt*) ; 

__attribute__((used)) static int seg6_local_fill_encap(struct sk_buff *skb,
				 struct lwtunnel_state *lwt)
{
	struct seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);
	struct seg6_action_param *param;
	int i, err;

	if (nla_put_u32(skb, SEG6_LOCAL_ACTION, slwt->action))
		return -EMSGSIZE;

	for (i = 0; i < SEG6_LOCAL_MAX + 1; i++) {
		if (slwt->desc->attrs & (1 << i)) {
			param = &seg6_action_params[i];
			err = param->put(skb, slwt);
			if (err < 0)
				return err;
		}
	}

	return 0;
}