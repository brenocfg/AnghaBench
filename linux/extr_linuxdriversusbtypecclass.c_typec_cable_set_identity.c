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
struct typec_cable {int /*<<< orphan*/  dev; int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  typec_report_identity (int /*<<< orphan*/ *) ; 

int typec_cable_set_identity(struct typec_cable *cable)
{
	if (!cable->identity)
		return -EINVAL;

	typec_report_identity(&cable->dev);
	return 0;
}