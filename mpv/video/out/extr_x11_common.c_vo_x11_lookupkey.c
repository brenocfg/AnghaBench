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

/* Variables and functions */
 int MP_KEY_UNKNOWN_RESERVED_LAST ; 
 int MP_KEY_UNKNOWN_RESERVED_START ; 
 int /*<<< orphan*/  keymap ; 
 int lookup_keymap_table (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char const*,int) ; 

__attribute__((used)) static int vo_x11_lookupkey(int key)
{
    const char *passthrough_keys = " -+*/<>`~!@#$%^&()_{}:;\"\',.?\\|=[]";
    int mpkey = 0;
    if ((key >= 'a' && key <= 'z') ||
        (key >= 'A' && key <= 'Z') ||
        (key >= '0' && key <= '9') ||
        (key > 0 && key < 256 && strchr(passthrough_keys, key)))
        mpkey = key;

    if (!mpkey)
        mpkey = lookup_keymap_table(keymap, key);

    // XFree86 keysym range; typically contains obscure "extra" keys
    if (!mpkey && key >= 0x10080001 && key <= 0x1008FFFF) {
        mpkey = MP_KEY_UNKNOWN_RESERVED_START + (key - 0x10080000);
        if (mpkey > MP_KEY_UNKNOWN_RESERVED_LAST)
            mpkey = 0;
    }

    return mpkey;
}