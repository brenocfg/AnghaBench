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
struct timeline {TYPE_1__* demuxer; } ;
struct dirent {char* d_name; } ;
struct bstr {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {char* filename; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct timeline*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct timeline*,char*,...) ; 
 struct bstr bstr0 (char*) ; 
 scalar_t__ bstr_case_startswith (struct bstr,struct bstr) ; 
 struct bstr bstr_strip_ext (struct bstr) ; 
 int /*<<< orphan*/  bstrdup0 (void*,struct bstr) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* mp_basename (char*) ; 
 struct bstr mp_dirname (char*) ; 
 char* mp_path_join_bstr (void*,struct bstr,struct bstr) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 scalar_t__ try_open (struct timeline*,char*) ; 

__attribute__((used)) static bool open_source(struct timeline *tl, char *filename)
{
    void *ctx = talloc_new(NULL);
    bool res = false;

    struct bstr dirname = mp_dirname(tl->demuxer->filename);

    struct bstr base_filename = bstr0(mp_basename(filename));
    if (!base_filename.len) {
        MP_WARN(tl, "CUE: Invalid audio filename in .cue file!\n");
    } else {
        char *fullname = mp_path_join_bstr(ctx, dirname, base_filename);
        if (try_open(tl, fullname)) {
            res = true;
            goto out;
        }
    }

    // Try an audio file with the same name as the .cue file (but different
    // extension).
    // Rationale: this situation happens easily if the audio file or both files
    // are renamed.

    struct bstr cuefile =
        bstr_strip_ext(bstr0(mp_basename(tl->demuxer->filename)));

    DIR *d = opendir(bstrdup0(ctx, dirname));
    if (!d)
        goto out;
    struct dirent *de;
    while ((de = readdir(d))) {
        char *dename0 = de->d_name;
        struct bstr dename = bstr0(dename0);
        if (bstr_case_startswith(dename, cuefile)) {
            MP_WARN(tl, "CUE: No useful audio filename "
                    "in .cue file found, trying with '%s' instead!\n",
                    dename0);
            if (try_open(tl, mp_path_join_bstr(ctx, dirname, dename))) {
                res = true;
                break;
            }
        }
    }
    closedir(d);

out:
    talloc_free(ctx);
    if (!res)
        MP_ERR(tl, "CUE: Could not open audio file!\n");
    return res;
}