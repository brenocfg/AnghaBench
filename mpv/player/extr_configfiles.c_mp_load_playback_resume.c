#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int /*<<< orphan*/  mconfig; TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  position_resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MSGL_V ; 
 int /*<<< orphan*/  M_SETOPT_PRESERVE_CMDLINE ; 
 int /*<<< orphan*/  m_config_backup_opt (int /*<<< orphan*/ ,char*) ; 
 char* mp_get_playback_resume_config_filename (struct MPContext*,char const*) ; 
 scalar_t__ mp_path_exists (char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  try_load_config (struct MPContext*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void mp_load_playback_resume(struct MPContext *mpctx, const char *file)
{
    if (!mpctx->opts->position_resume)
        return;
    char *fname = mp_get_playback_resume_config_filename(mpctx, file);
    if (fname && mp_path_exists(fname)) {
        // Never apply the saved start position to following files
        m_config_backup_opt(mpctx->mconfig, "start");
        MP_INFO(mpctx, "Resuming playback. This behavior can "
               "be disabled with --no-resume-playback.\n");
        try_load_config(mpctx, fname, M_SETOPT_PRESERVE_CMDLINE, MSGL_V);
        unlink(fname);
    }
    talloc_free(fname);
}