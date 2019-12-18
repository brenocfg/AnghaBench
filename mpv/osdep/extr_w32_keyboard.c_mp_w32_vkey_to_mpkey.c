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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int lookup_keymap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vk_map ; 
 int /*<<< orphan*/  vk_map_ext ; 

int mp_w32_vkey_to_mpkey(UINT vkey, bool extended)
{
    // The extended flag is set for the navigation cluster and the arrow keys,
    // so it can be used to differentiate between them and the numpad. The
    // numpad enter key also has this flag set.
    int mpkey = lookup_keymap(extended ? vk_map_ext : vk_map, vkey);

    // If we got the extended flag for a key we don't recognize, search the
    // normal keymap before giving up
    if (extended && !mpkey)
        mpkey = lookup_keymap(vk_map, vkey);

    return mpkey;
}