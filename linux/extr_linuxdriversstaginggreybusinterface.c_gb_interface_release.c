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
struct gb_interface {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gb_interface*) ; 
 struct gb_interface* to_gb_interface (struct device*) ; 
 int /*<<< orphan*/  trace_gb_interface_release (struct gb_interface*) ; 

__attribute__((used)) static void gb_interface_release(struct device *dev)
{
	struct gb_interface *intf = to_gb_interface(dev);

	trace_gb_interface_release(intf);

	kfree(intf);
}