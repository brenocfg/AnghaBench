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
struct slim_device_id {scalar_t__ manf_id; scalar_t__ prod_code; } ;
struct TYPE_2__ {scalar_t__ manf_id; scalar_t__ prod_code; } ;
struct slim_device {TYPE_1__ e_addr; } ;

/* Variables and functions */

__attribute__((used)) static const struct slim_device_id *slim_match(const struct slim_device_id *id,
					       const struct slim_device *sbdev)
{
	while (id->manf_id != 0 || id->prod_code != 0) {
		if (id->manf_id == sbdev->e_addr.manf_id &&
		    id->prod_code == sbdev->e_addr.prod_code)
			return id;
		id++;
	}
	return NULL;
}