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
typedef  int /*<<< orphan*/  wchar_t ;
struct vo_w32_state {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int decode_utf16 (struct vo_w32_state*,int /*<<< orphan*/ ) ; 
 int mod_state (struct vo_w32_state*) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool handle_char(struct vo_w32_state *w32, wchar_t wc)
{
    int c = decode_utf16(w32, wc);

    if (c == 0)
        return true;
    if (c < 0x20)
        return false;

    mp_input_put_key(w32->input_ctx, c | mod_state(w32));
    return true;
}