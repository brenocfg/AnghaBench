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
typedef  int /*<<< orphan*/  uint8_t ;
struct MPOpts {char* watch_later_directory; scalar_t__ ignore_path_in_watch_later_config; } ;
struct MPContext {char* cached_watch_later_configdir; int /*<<< orphan*/  global; struct MPOpts* opts; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WATCH_LATER_CONF ; 
 int /*<<< orphan*/  av_md5_sum (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (char const*) ; 
 char* mp_basename (char const*) ; 
 char* mp_find_user_config_file (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mp_get_user_path (struct MPContext*,int /*<<< orphan*/ ,char*) ; 
 char* mp_getcwd (void*) ; 
 int /*<<< orphan*/  mp_is_url (int /*<<< orphan*/ ) ; 
 void* mp_path_join (void*,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* talloc_asprintf_append (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static char *mp_get_playback_resume_config_filename(struct MPContext *mpctx,
                                                    const char *fname)
{
    struct MPOpts *opts = mpctx->opts;
    char *res = NULL;
    void *tmp = talloc_new(NULL);
    const char *realpath = fname;
    bstr bfname = bstr0(fname);
    if (!mp_is_url(bfname)) {
        if (opts->ignore_path_in_watch_later_config) {
            realpath = mp_basename(fname);
        } else {
            char *cwd = mp_getcwd(tmp);
            if (!cwd)
                goto exit;
            realpath = mp_path_join(tmp, cwd, fname);
        }
    }
    uint8_t md5[16];
    av_md5_sum(md5, realpath, strlen(realpath));
    char *conf = talloc_strdup(tmp, "");
    for (int i = 0; i < 16; i++)
        conf = talloc_asprintf_append(conf, "%02X", md5[i]);

    if (!mpctx->cached_watch_later_configdir) {
        char *wl_dir = mpctx->opts->watch_later_directory;
        if (wl_dir && wl_dir[0]) {
            mpctx->cached_watch_later_configdir =
                mp_get_user_path(mpctx, mpctx->global, wl_dir);
        }
    }

    if (!mpctx->cached_watch_later_configdir) {
        mpctx->cached_watch_later_configdir =
            mp_find_user_config_file(mpctx, mpctx->global, MP_WATCH_LATER_CONF);
    }

    if (mpctx->cached_watch_later_configdir)
        res = mp_path_join(NULL, mpctx->cached_watch_later_configdir, conf);

exit:
    talloc_free(tmp);
    return res;
}