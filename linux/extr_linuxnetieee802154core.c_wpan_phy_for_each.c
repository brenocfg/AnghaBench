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
struct wpan_phy_iter_data {int (* fn ) (struct wpan_phy*,void*) ;void* data; } ;

/* Variables and functions */
 int class_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wpan_phy_iter_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpan_phy_class ; 
 int /*<<< orphan*/  wpan_phy_iter ; 

int wpan_phy_for_each(int (*fn)(struct wpan_phy *phy, void *data),
		      void *data)
{
	struct wpan_phy_iter_data wpid = {
		.fn = fn,
		.data = data,
	};

	return class_for_each_device(&wpan_phy_class, NULL,
			&wpid, wpan_phy_iter);
}