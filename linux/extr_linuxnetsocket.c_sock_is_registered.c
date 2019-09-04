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

/* Variables and functions */
 int NPROTO ; 
 int /*<<< orphan*/ * net_families ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

bool sock_is_registered(int family)
{
	return family < NPROTO && rcu_access_pointer(net_families[family]);
}