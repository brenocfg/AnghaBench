#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct priv {int broken_seek; scalar_t__ entry_size; TYPE_3__* mpa; } ;
struct TYPE_9__ {scalar_t__ pos; int /*<<< orphan*/  cancel; struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_10__ {int /*<<< orphan*/  arch; int /*<<< orphan*/  locale; } ;

/* Variables and functions */
 int MPMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ STREAM_OK ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ ) ; 
 int archive_read_data (int /*<<< orphan*/ ,char*,int) ; 
 int archive_seek_data (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_archive_check_fatal (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mp_archive_free (TYPE_3__*) ; 
 scalar_t__ mp_cancel_test (int /*<<< orphan*/ ) ; 
 scalar_t__ reopen_archive (TYPE_1__*) ; 
 int /*<<< orphan*/  uselocale (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int archive_entry_seek(stream_t *s, int64_t newpos)
{
    struct priv *p = s->priv;
    if (p->mpa && !p->broken_seek) {
        locale_t oldlocale = uselocale(p->mpa->locale);
        int r = archive_seek_data(p->mpa->arch, newpos, SEEK_SET);
        uselocale(oldlocale);
        if (r >= 0)
            return 1;
        MP_WARN(s, "possibly unsupported seeking - switching to reopening\n");
        p->broken_seek = true;
        if (reopen_archive(s) < STREAM_OK)
            return -1;
    }
    // libarchive can't seek in most formats.
    if (newpos < s->pos) {
        // Hack seeking backwards into working by reopening the archive and
        // starting over.
        MP_VERBOSE(s, "trying to reopen archive for performing seek\n");
        if (reopen_archive(s) < STREAM_OK)
            return -1;
    }
    if (newpos > s->pos) {
        if (!p->mpa && reopen_archive(s) < STREAM_OK)
            return -1;
        // For seeking forwards, just keep reading data (there's no libarchive
        // skip function either).
        char buffer[4096];
        while (newpos > s->pos) {
            if (mp_cancel_test(s->cancel))
                return -1;

            int size = MPMIN(newpos - s->pos, sizeof(buffer));
            locale_t oldlocale = uselocale(p->mpa->locale);
            int r = archive_read_data(p->mpa->arch, buffer, size);
            if (r <= 0) {
                if (r == 0 && newpos > p->entry_size) {
                    MP_ERR(s, "demuxer trying to seek beyond end of archive "
                           "entry\n");
                } else if (r == 0) {
                    MP_ERR(s, "end of archive entry reached while seeking\n");
                } else {
                    MP_ERR(s, "%s\n", archive_error_string(p->mpa->arch));
                }
                uselocale(oldlocale);
                if (mp_archive_check_fatal(p->mpa, r)) {
                    mp_archive_free(p->mpa);
                    p->mpa = NULL;
                }
                return -1;
            }
            uselocale(oldlocale);
            s->pos += r;
        }
    }
    return 1;
}