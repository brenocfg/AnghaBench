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
struct priv {int entry_size; int /*<<< orphan*/  entry_name; struct mp_archive* mpa; int /*<<< orphan*/  src; } ;
struct mp_archive {int /*<<< orphan*/  entry; int /*<<< orphan*/  locale; int /*<<< orphan*/  entry_filename; } ;
struct TYPE_4__ {int /*<<< orphan*/  log; scalar_t__ pos; struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ARCHIVE_FLAG_UNSAFE ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int archive_entry_size (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_size_is_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_archive_free (struct mp_archive*) ; 
 struct mp_archive* mp_archive_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_archive_next_entry (struct mp_archive*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uselocale (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reopen_archive(stream_t *s)
{
    struct priv *p = s->priv;
    mp_archive_free(p->mpa);
    s->pos = 0;
    p->mpa = mp_archive_new(s->log, p->src, MP_ARCHIVE_FLAG_UNSAFE);
    if (!p->mpa)
        return STREAM_ERROR;

    // Follows the same logic as demux_libarchive.c.
    struct mp_archive *mpa = p->mpa;
    while (mp_archive_next_entry(mpa)) {
        if (strcmp(p->entry_name, mpa->entry_filename) == 0) {
            locale_t oldlocale = uselocale(mpa->locale);
            p->entry_size = -1;
            if (archive_entry_size_is_set(mpa->entry))
                p->entry_size = archive_entry_size(mpa->entry);
            uselocale(oldlocale);
            return STREAM_OK;
        }
    }

    mp_archive_free(p->mpa);
    p->mpa = NULL;
    MP_ERR(s, "archive entry not found. '%s'\n", p->entry_name);
    return STREAM_ERROR;
}