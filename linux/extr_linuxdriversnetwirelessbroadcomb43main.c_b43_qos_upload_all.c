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
struct b43_wldev {int /*<<< orphan*/  qos_enabled; struct b43_wl* wl; } ;
struct b43_wl {struct b43_qos_params* qos_params; } ;
struct b43_qos_params {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_qos_params*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_qos_params_upload (struct b43_wldev*,int /*<<< orphan*/ *,struct b43_qos_params) ; 
 struct b43_qos_params* b43_qos_shm_offsets ; 

__attribute__((used)) static void b43_qos_upload_all(struct b43_wldev *dev)
{
	struct b43_wl *wl = dev->wl;
	struct b43_qos_params *params;
	unsigned int i;

	if (!dev->qos_enabled)
		return;

	BUILD_BUG_ON(ARRAY_SIZE(b43_qos_shm_offsets) !=
		     ARRAY_SIZE(wl->qos_params));

	b43_mac_suspend(dev);
	for (i = 0; i < ARRAY_SIZE(wl->qos_params); i++) {
		params = &(wl->qos_params[i]);
		b43_qos_params_upload(dev, &(params->p),
				      b43_qos_shm_offsets[i]);
	}
	b43_mac_enable(dev);
}