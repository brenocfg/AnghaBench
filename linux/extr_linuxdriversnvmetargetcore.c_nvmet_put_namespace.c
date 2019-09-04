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
struct nvmet_ns {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 

void nvmet_put_namespace(struct nvmet_ns *ns)
{
	percpu_ref_put(&ns->ref);
}