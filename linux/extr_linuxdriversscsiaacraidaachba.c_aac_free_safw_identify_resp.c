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
struct aac_dev {TYPE_1__** hba_map; } ;
struct TYPE_2__ {int /*<<< orphan*/ * safw_identify_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void aac_free_safw_identify_resp(struct aac_dev *dev,
						int bus, int target)
{
	kfree(dev->hba_map[bus][target].safw_identify_resp);
	dev->hba_map[bus][target].safw_identify_resp = NULL;
}