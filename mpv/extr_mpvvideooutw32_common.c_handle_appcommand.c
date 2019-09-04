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

/* Variables and functions */
 int mod_state (struct vo_w32_state*) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_use_media_keys (int /*<<< orphan*/ ) ; 
 int mp_w32_appcmd_to_mpkey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_appcommand(struct vo_w32_state *w32, UINT cmd)
{
    if (!mp_input_use_media_keys(w32->input_ctx))
        return false;
    int mpkey = mp_w32_appcmd_to_mpkey(cmd);
    if (!mpkey)
        return false;
    mp_input_put_key(w32->input_ctx, mpkey | mod_state(w32));
    return true;
}