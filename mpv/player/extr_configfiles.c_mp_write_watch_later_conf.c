#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct playlist_entry {int num_redirects; char** redirects; int /*<<< orphan*/  filename; } ;
struct demuxer {scalar_t__ partially_seekable; int /*<<< orphan*/  seekable; } ;
struct MPContext {char** resume_defaults; int /*<<< orphan*/  cached_watch_later_configdir; int /*<<< orphan*/  global; struct demuxer* demuxer; struct playlist_entry* playing; } ;
struct TYPE_4__ {int len; } ;
typedef  TYPE_1__ bstr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*) ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  M_PROPERTY_GET_STRING ; 
 int M_PROPERTY_OK ; 
 char** backup_properties ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 scalar_t__ bstr_equals0 (TYPE_1__,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 double get_current_time (struct MPContext*) ; 
 TYPE_1__ mp_dirname (char*) ; 
 char* mp_get_playback_resume_config_filename (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_is_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_mk_config_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_path_strip_trailing_separator (char*) ; 
 int mp_property_do (char const*,int /*<<< orphan*/ ,char**,struct MPContext*) ; 
 scalar_t__ needs_config_quoting (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  write_filename (struct MPContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_redirect (struct MPContext*,char*) ; 

void mp_write_watch_later_conf(struct MPContext *mpctx)
{
    struct playlist_entry *cur = mpctx->playing;
    char *conffile = NULL;
    if (!cur)
        goto exit;

    struct demuxer *demux = mpctx->demuxer;
    if (demux && (!demux->seekable || demux->partially_seekable)) {
        MP_INFO(mpctx, "Not seekable - not saving state.\n");
        goto exit;
    }

    conffile = mp_get_playback_resume_config_filename(mpctx, cur->filename);
    if (!conffile)
        goto exit;

    mp_mk_config_dir(mpctx->global, mpctx->cached_watch_later_configdir);

    MP_INFO(mpctx, "Saving state.\n");

    FILE *file = fopen(conffile, "wb");
    if (!file)
        goto exit;

    write_filename(mpctx, file, cur->filename);

    double pos = get_current_time(mpctx);
    if (pos != MP_NOPTS_VALUE)
        fprintf(file, "start=%f\n", pos);
    for (int i = 0; backup_properties[i]; i++) {
        const char *pname = backup_properties[i];
        char *val = NULL;
        int r = mp_property_do(pname, M_PROPERTY_GET_STRING, &val, mpctx);
        if (r == M_PROPERTY_OK) {
            if (strncmp(pname, "options/", 8) == 0)
                pname += 8;
            // Only store it if it's different from the initial value.
            char *prev = mpctx->resume_defaults[i];
            if (!prev || strcmp(prev, val) != 0) {
                if (needs_config_quoting(val)) {
                    // e.g. '%6%STRING'
                    fprintf(file, "%s=%%%d%%%s\n", pname, (int)strlen(val), val);
                } else {
                    fprintf(file, "%s=%s\n", pname, val);
                }
            }
        }
        talloc_free(val);
    }
    fclose(file);

    // This allows us to recursively resume directories etc., whose entries are
    // expanded the first time it's "played". For example, if "/a/b/c.mkv" is
    // the current entry, then we want to resume this file if the user does
    // "mpv /a". This would expand to the directory entries in "/a", and if
    // "/a/a.mkv" is not the first entry, this would be played.
    // Here, we write resume entries for "/a" and "/a/b".
    // (Unfortunately, this will leave stray resume files on resume, because
    // obviously it resumes only from one of those paths.)
    for (int n = 0; n < cur->num_redirects; n++)
        write_redirect(mpctx, cur->redirects[n]);
    // And at last, for local directories, we write an entry for each path
    // prefix, so the user can resume from an arbitrary directory. This starts
    // with the first redirect (all other redirects are further prefixes).
    if (cur->num_redirects) {
        char *path = cur->redirects[0];
        char tmp[4096];
        if (!mp_is_url(bstr0(path)) && strlen(path) < sizeof(tmp)) {
            snprintf(tmp, sizeof(tmp), "%s", path);
            for (;;) {
                bstr dir = mp_dirname(tmp);
                if (dir.len == strlen(tmp) || !dir.len || bstr_equals0(dir, "."))
                    break;

                tmp[dir.len] = '\0';
                if (strlen(tmp) >= 2) // keep "/"
                    mp_path_strip_trailing_separator(tmp);
                write_redirect(mpctx, tmp);
            }
        }
    }

exit:
    talloc_free(conffile);
}