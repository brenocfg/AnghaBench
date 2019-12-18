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
struct TYPE_2__ {int icmp_strict_tag_validation; } ;

/* Variables and functions */
 int /*<<< orphan*/ * inet_protos ; 
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool icmp_tag_validation(int proto)
{
	bool ok;

	rcu_read_lock();
	ok = rcu_dereference(inet_protos[proto])->icmp_strict_tag_validation;
	rcu_read_unlock();
	return ok;
}