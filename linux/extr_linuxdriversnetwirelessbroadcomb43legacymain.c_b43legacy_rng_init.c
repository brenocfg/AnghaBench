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
struct b43legacy_wl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int b43legacy_rng_init(struct b43legacy_wl *wl)
{
	int err = 0;

#ifdef CONFIG_B43LEGACY_HWRNG
	snprintf(wl->rng_name, ARRAY_SIZE(wl->rng_name),
		 "%s_%s", KBUILD_MODNAME, wiphy_name(wl->hw->wiphy));
	wl->rng.name = wl->rng_name;
	wl->rng.data_read = b43legacy_rng_read;
	wl->rng.priv = (unsigned long)wl;
	wl->rng_initialized = 1;
	err = hwrng_register(&wl->rng);
	if (err) {
		wl->rng_initialized = 0;
		b43legacyerr(wl, "Failed to register the random "
		       "number generator (%d)\n", err);
	}

#endif
	return err;
}