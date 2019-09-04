#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* keys; int /*<<< orphan*/ * manager; int /*<<< orphan*/ * layout_data; int /*<<< orphan*/ * tis; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;
struct TYPE_6__ {size_t num; int /*<<< orphan*/ ** array; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_3__) ; 

__attribute__((used)) static inline void free_hotkeys_platform(obs_hotkeys_platform_t *plat)
{
	if (!plat)
		return;

	if (plat->tis) {
		CFRelease(plat->tis);
		plat->tis = NULL;
	}

	if (plat->layout_data) {
		CFRelease(plat->layout_data);
		plat->layout_data = NULL;
	}

	if (plat->manager) {
		CFRelease(plat->manager);
		plat->manager = NULL;
	}

	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++) {
		for (size_t j = 0; j < plat->keys[i].num; j++)
			CFRelease(plat->keys[i].array[j]);

		da_free(plat->keys[i]);
	}

	bfree(plat);
}