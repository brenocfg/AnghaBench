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
struct MPContext {int /*<<< orphan*/  mconfig; int /*<<< orphan*/  global; } ;

/* Variables and functions */
 int m_config_parse_config_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 char* mp_get_user_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int cfg_include(void *ctx, char *filename, int flags)
{
    struct MPContext *mpctx = ctx;
    char *fname = mp_get_user_path(NULL, mpctx->global, filename);
    int r = m_config_parse_config_file(mpctx->mconfig, fname, NULL, flags);
    talloc_free(fname);
    return r;
}