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
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_stp_set_enabled (struct net_bridge*,unsigned long) ; 

__attribute__((used)) static int set_stp_state(struct net_bridge *br, unsigned long val)
{
	br_stp_set_enabled(br, val);

	return 0;
}