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
 int /*<<< orphan*/  cmpxchg (struct lwtunnel_encap_ops const**,int /*<<< orphan*/ *,struct lwtunnel_encap_ops const*) ; 
 int /*<<< orphan*/ * lwtun_encaps ; 

int lwtunnel_encap_add_ops(const struct lwtunnel_encap_ops *ops,
			   unsigned int num)
{
	if (num > LWTUNNEL_ENCAP_MAX)
		return -ERANGE;

	return !cmpxchg((const struct lwtunnel_encap_ops **)
			&lwtun_encaps[num],
			NULL, ops) ? 0 : -1;
}