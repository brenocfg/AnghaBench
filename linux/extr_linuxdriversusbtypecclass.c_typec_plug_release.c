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
struct typec_plug {int /*<<< orphan*/  mode_ids; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct typec_plug*) ; 
 struct typec_plug* to_typec_plug (struct device*) ; 

__attribute__((used)) static void typec_plug_release(struct device *dev)
{
	struct typec_plug *plug = to_typec_plug(dev);

	ida_destroy(&plug->mode_ids);
	kfree(plug);
}