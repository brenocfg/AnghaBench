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
struct nvme_subsystem {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  nvme_subsystems_ida ; 

__attribute__((used)) static void __nvme_release_subsystem(struct nvme_subsystem *subsys)
{
	ida_simple_remove(&nvme_subsystems_ida, subsys->instance);
	kfree(subsys);
}