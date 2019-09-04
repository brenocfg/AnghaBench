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
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_stp_set_bridge_priority (struct net_bridge*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_priority(struct net_bridge *br, unsigned long val)
{
	br_stp_set_bridge_priority(br, (u16) val);
	return 0;
}