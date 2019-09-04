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
struct MPContext {int /*<<< orphan*/  mconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MSG (struct MPContext*,int,char*,char const*) ; 
 int /*<<< orphan*/  m_config_parse_config_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_path_exists (char const*) ; 

__attribute__((used)) static int try_load_config(struct MPContext *mpctx, const char *file, int flags,
                           int msgl)
{
    if (!mp_path_exists(file))
        return 0;
    MP_MSG(mpctx, msgl, "Loading config '%s'\n", file);
    m_config_parse_config_file(mpctx->mconfig, file, NULL, flags);
    return 1;
}