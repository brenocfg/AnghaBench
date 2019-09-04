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

/* Variables and functions */
 int MP_KEY_MODIFIER_ALT ; 
 int MP_KEY_MODIFIER_CTRL ; 
 int MP_KEY_MODIFIER_SHIFT ; 
 int /*<<< orphan*/  VK_LCONTROL ; 
 int /*<<< orphan*/  VK_LMENU ; 
 int /*<<< orphan*/  VK_RCONTROL ; 
 int /*<<< orphan*/  VK_RMENU ; 
 int /*<<< orphan*/  VK_SHIFT ; 
 scalar_t__ key_state (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_input_use_alt_gr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mod_state(struct vo_w32_state *w32)
{
    int res = 0;

    // AltGr is represented as LCONTROL+RMENU on Windows
    bool alt_gr = mp_input_use_alt_gr(w32->input_ctx) &&
        key_state(VK_RMENU) && key_state(VK_LCONTROL);

    if (key_state(VK_RCONTROL) || (key_state(VK_LCONTROL) && !alt_gr))
        res |= MP_KEY_MODIFIER_CTRL;
    if (key_state(VK_SHIFT))
        res |= MP_KEY_MODIFIER_SHIFT;
    if (key_state(VK_LMENU) || (key_state(VK_RMENU) && !alt_gr))
        res |= MP_KEY_MODIFIER_ALT;
    return res;
}