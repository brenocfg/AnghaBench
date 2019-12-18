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
struct sw_flow_actions {scalar_t__ actions_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sw_flow_actions* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ACTIONS_BUFSIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct sw_flow_actions* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sw_flow_actions *nla_alloc_flow_actions(int size)
{
	struct sw_flow_actions *sfa;

	WARN_ON_ONCE(size > MAX_ACTIONS_BUFSIZE);

	sfa = kmalloc(sizeof(*sfa) + size, GFP_KERNEL);
	if (!sfa)
		return ERR_PTR(-ENOMEM);

	sfa->actions_len = 0;
	return sfa;
}