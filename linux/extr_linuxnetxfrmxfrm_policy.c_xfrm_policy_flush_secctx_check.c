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
typedef  int /*<<< orphan*/  u8 ;
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfrm_policy_flush_secctx_check(struct net *net, u8 type, bool task_valid)
{
	return 0;
}