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
struct firmware {int dummy; } ;
struct b43legacy_wldev {int /*<<< orphan*/  fw_load_complete; struct firmware const* fwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_fw_cb(const struct firmware *firmware, void *context)
{
	struct b43legacy_wldev *dev = context;

	dev->fwp = firmware;
	complete(&dev->fw_load_complete);
}