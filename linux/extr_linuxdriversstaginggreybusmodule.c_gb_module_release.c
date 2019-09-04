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
struct gb_module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gb_module*) ; 
 struct gb_module* to_gb_module (struct device*) ; 
 int /*<<< orphan*/  trace_gb_module_release (struct gb_module*) ; 

__attribute__((used)) static void gb_module_release(struct device *dev)
{
	struct gb_module *module = to_gb_module(dev);

	trace_gb_module_release(module);

	kfree(module);
}