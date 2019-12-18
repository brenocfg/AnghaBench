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
struct caif_device_entry {int /*<<< orphan*/ * pcpu_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void caifd_hold(struct caif_device_entry *e)
{
	this_cpu_inc(*e->pcpu_refcnt);
}