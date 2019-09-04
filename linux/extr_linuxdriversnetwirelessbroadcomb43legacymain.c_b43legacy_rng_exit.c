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

__attribute__((used)) static void b43legacy_rng_exit(struct b43legacy_wl *wl)
{
#ifdef CONFIG_B43LEGACY_HWRNG
	if (wl->rng_initialized)
		hwrng_unregister(&wl->rng);
#endif
}