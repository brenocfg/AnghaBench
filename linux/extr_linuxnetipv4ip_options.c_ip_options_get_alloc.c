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
struct ip_options_rcu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ip_options_rcu* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip_options_rcu *ip_options_get_alloc(const int optlen)
{
	return kzalloc(sizeof(struct ip_options_rcu) + ((optlen + 3) & ~3),
		       GFP_KERNEL);
}