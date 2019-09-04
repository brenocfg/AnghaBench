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
struct TYPE_2__ {scalar_t__ next_heartbeat; } ;

/* Variables and functions */
 int HZ ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 TYPE_1__ pikawdt_private ; 

__attribute__((used)) static void pikawdt_keepalive(void)
{
	pikawdt_private.next_heartbeat = jiffies + heartbeat * HZ;
}