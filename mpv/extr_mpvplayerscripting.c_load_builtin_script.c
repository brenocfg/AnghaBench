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
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_SHUTDOWN ; 
 int mp_client_exists (struct MPContext*,char*) ; 
 int /*<<< orphan*/  mp_client_send_event (struct MPContext*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_load_script (struct MPContext*,char const*) ; 
 char* script_name_from_filename (void*,char const*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_builtin_script(struct MPContext *mpctx, bool enable,
                                const char *fname)
{
    void *tmp = talloc_new(NULL);
    // (The name doesn't have to match if there were conflicts with other
    // scripts, so this is on best-effort basis.)
    char *name = script_name_from_filename(tmp, fname);
    if (enable != mp_client_exists(mpctx, name)) {
        if (enable) {
            mp_load_script(mpctx, fname);
        } else {
            // Try to unload it by sending a shutdown event. This can be
            // unreliable, because user scripts could have clashing names, or
            // disabling and then quickly re-enabling a builtin script might
            // detect the still-terminating script as loaded.
            mp_client_send_event(mpctx, name, 0, MPV_EVENT_SHUTDOWN, NULL);
        }
    }
    talloc_free(tmp);
}