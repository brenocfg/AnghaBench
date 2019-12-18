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
struct vo_w32_state {int /*<<< orphan*/  input_ctx; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetKeyboardState (int*) ; 
 size_t VK_CONTROL ; 
 size_t VK_LCONTROL ; 
 size_t VK_LMENU ; 
 size_t VK_MENU ; 
 size_t VK_RCONTROL ; 
 size_t VK_RMENU ; 
 int decode_utf16 (struct vo_w32_state*,int) ; 
 int /*<<< orphan*/  mp_input_use_alt_gr (int /*<<< orphan*/ ) ; 
 int to_unicode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int decode_key(struct vo_w32_state *w32, UINT vkey, UINT scancode)
{
    BYTE keys[256];
    GetKeyboardState(keys);

    // If mp_input_use_alt_gr is false, detect and remove AltGr so normal
    // characters are generated. Note that AltGr is represented as
    // LCONTROL+RMENU on Windows.
    if ((keys[VK_RMENU] & 0x80) && (keys[VK_LCONTROL] & 0x80) &&
        !mp_input_use_alt_gr(w32->input_ctx))
    {
        keys[VK_RMENU] = keys[VK_LCONTROL] = 0;
        keys[VK_MENU] = keys[VK_LMENU];
        keys[VK_CONTROL] = keys[VK_RCONTROL];
    }

    int c = to_unicode(vkey, scancode, keys);

    // Some shift states prevent ToUnicode from working or cause it to produce
    // control characters. If this is detected, remove modifiers until it
    // starts producing normal characters.
    if (c < 0x20 && (keys[VK_MENU] & 0x80)) {
        keys[VK_LMENU] = keys[VK_RMENU] = keys[VK_MENU] = 0;
        c = to_unicode(vkey, scancode, keys);
    }
    if (c < 0x20 && (keys[VK_CONTROL] & 0x80)) {
        keys[VK_LCONTROL] = keys[VK_RCONTROL] = keys[VK_CONTROL] = 0;
        c = to_unicode(vkey, scancode, keys);
    }
    if (c < 0x20)
        return 0;

    // Decode lone UTF-16 surrogates (VK_PACKET can generate these)
    if (c < 0x10000)
        return decode_utf16(w32, c);
    return c;
}