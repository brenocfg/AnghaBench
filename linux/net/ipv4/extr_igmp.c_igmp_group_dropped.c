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
struct ip_mc_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __igmp_group_dropped (struct ip_mc_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igmp_group_dropped(struct ip_mc_list *im)
{
	__igmp_group_dropped(im, GFP_KERNEL);
}