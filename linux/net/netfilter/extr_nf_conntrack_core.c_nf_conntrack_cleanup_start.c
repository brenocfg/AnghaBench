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
struct TYPE_2__ {int exiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ conntrack_gc_work ; 
 int /*<<< orphan*/  ip_ct_attach ; 

void nf_conntrack_cleanup_start(void)
{
	conntrack_gc_work.exiting = true;
	RCU_INIT_POINTER(ip_ct_attach, NULL);
}