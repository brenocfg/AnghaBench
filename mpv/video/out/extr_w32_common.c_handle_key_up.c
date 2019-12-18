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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INPUT_RELEASE_ALL ; 
#define  VK_CONTROL 130 
#define  VK_MENU 129 
#define  VK_SHIFT 128 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_key_up(struct vo_w32_state *w32, UINT vkey, UINT scancode)
{
    switch (vkey) {
    case VK_MENU:
    case VK_CONTROL:
    case VK_SHIFT:
        break;
    default:
        // Releasing all keys on key-up is simpler and ensures no keys can be
        // get "stuck." This matches the behaviour of other VOs.
        mp_input_put_key(w32->input_ctx, MP_INPUT_RELEASE_ALL);
    }
}