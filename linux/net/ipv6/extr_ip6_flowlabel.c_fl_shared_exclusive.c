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
struct ip6_flowlabel {scalar_t__ share; } ;

/* Variables and functions */
 scalar_t__ IPV6_FL_S_EXCL ; 
 scalar_t__ IPV6_FL_S_PROCESS ; 
 scalar_t__ IPV6_FL_S_USER ; 

__attribute__((used)) static bool fl_shared_exclusive(struct ip6_flowlabel *fl)
{
	return fl->share == IPV6_FL_S_EXCL ||
	       fl->share == IPV6_FL_S_PROCESS ||
	       fl->share == IPV6_FL_S_USER;
}