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
struct tipc_member {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MBR_JOINING ; 
 scalar_t__ MBR_PUBLISHED ; 

__attribute__((used)) static bool tipc_group_is_sender(struct tipc_member *m)
{
	return m && m->state != MBR_JOINING && m->state != MBR_PUBLISHED;
}