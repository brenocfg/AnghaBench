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
struct seg6_local_lwt {scalar_t__ action; TYPE_1__* desc; } ;
struct seg6_action_param {scalar_t__ (* cmp ) (struct seg6_local_lwt*,struct seg6_local_lwt*) ;} ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_2__ {int attrs; } ;

/* Variables and functions */
 int SEG6_LOCAL_MAX ; 
 struct seg6_action_param* seg6_action_params ; 
 struct seg6_local_lwt* seg6_local_lwtunnel (struct lwtunnel_state*) ; 
 scalar_t__ stub1 (struct seg6_local_lwt*,struct seg6_local_lwt*) ; 

__attribute__((used)) static int seg6_local_cmp_encap(struct lwtunnel_state *a,
				struct lwtunnel_state *b)
{
	struct seg6_local_lwt *slwt_a, *slwt_b;
	struct seg6_action_param *param;
	int i;

	slwt_a = seg6_local_lwtunnel(a);
	slwt_b = seg6_local_lwtunnel(b);

	if (slwt_a->action != slwt_b->action)
		return 1;

	if (slwt_a->desc->attrs != slwt_b->desc->attrs)
		return 1;

	for (i = 0; i < SEG6_LOCAL_MAX + 1; i++) {
		if (slwt_a->desc->attrs & (1 << i)) {
			param = &seg6_action_params[i];
			if (param->cmp(slwt_a, slwt_b))
				return 1;
		}
	}

	return 0;
}