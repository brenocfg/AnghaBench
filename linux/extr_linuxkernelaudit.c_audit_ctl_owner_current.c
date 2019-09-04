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
struct TYPE_2__ {scalar_t__ owner; } ;

/* Variables and functions */
 TYPE_1__ audit_cmd_mutex ; 
 scalar_t__ current ; 

__attribute__((used)) static bool audit_ctl_owner_current(void)
{
	return (current == audit_cmd_mutex.owner);
}