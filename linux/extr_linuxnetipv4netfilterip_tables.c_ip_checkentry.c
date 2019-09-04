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
struct ipt_ip {int flags; int invflags; } ;

/* Variables and functions */
 int IPT_F_MASK ; 
 int IPT_INV_MASK ; 

__attribute__((used)) static bool
ip_checkentry(const struct ipt_ip *ip)
{
	if (ip->flags & ~IPT_F_MASK)
		return false;
	if (ip->invflags & ~IPT_INV_MASK)
		return false;
	return true;
}