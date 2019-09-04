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
struct MPContext {int /*<<< orphan*/  global; } ;

/* Variables and functions */
 char* mp_get_user_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int mp_load_script (struct MPContext*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

int mp_load_user_script(struct MPContext *mpctx, const char *fname)
{
    char *path = mp_get_user_path(NULL, mpctx->global, fname);
    int ret = mp_load_script(mpctx, path);
    talloc_free(path);
    return ret;
}