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
struct lwtunnel_encap_ops {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 unsigned int LWTUNNEL_ENCAP_MAX ; 
 unsigned int LWTUNNEL_ENCAP_NONE ; 
 struct lwtunnel_encap_ops const* cmpxchg (struct lwtunnel_encap_ops const**,struct lwtunnel_encap_ops const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lwtun_encaps ; 
 int /*<<< orphan*/  synchronize_net () ; 

int lwtunnel_encap_del_ops(const struct lwtunnel_encap_ops *ops,
			   unsigned int encap_type)
{
	int ret;

	if (encap_type == LWTUNNEL_ENCAP_NONE ||
	    encap_type > LWTUNNEL_ENCAP_MAX)
		return -ERANGE;

	ret = (cmpxchg((const struct lwtunnel_encap_ops **)
		       &lwtun_encaps[encap_type],
		       ops, NULL) == ops) ? 0 : -1;

	synchronize_net();

	return ret;
}