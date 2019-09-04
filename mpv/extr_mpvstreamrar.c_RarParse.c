#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct stream {int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; int /*<<< orphan*/  url; } ;
struct TYPE_12__ {int start; int const stop; int /*<<< orphan*/  format; int /*<<< orphan*/  match; } ;
typedef  TYPE_1__ rar_pattern_t ;
struct TYPE_13__ {int /*<<< orphan*/  is_complete; } ;
typedef  TYPE_2__ rar_file_t ;
struct TYPE_14__ {int type; int flags; } ;
typedef  TYPE_3__ rar_block_t ;

/* Variables and functions */
 TYPE_1__* FindVolumePattern (int /*<<< orphan*/ ) ; 
 scalar_t__ IgnoreBlock (struct stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ PeekBlock (struct stream*,TYPE_3__*) ; 
 int /*<<< orphan*/  RAR_BLOCK_ARCHIVE ; 
#define  RAR_BLOCK_END 129 
 int RAR_BLOCK_END_HAS_NEXT ; 
#define  RAR_BLOCK_FILE 128 
 int /*<<< orphan*/  RAR_BLOCK_MARKER ; 
 int /*<<< orphan*/  STREAM_READ ; 
 int SkipBlock (struct stream*,TYPE_3__*) ; 
 int SkipEnd (struct stream*,TYPE_3__*) ; 
 int SkipFile (struct stream*,int*,TYPE_2__***,TYPE_3__*,char*) ; 
 scalar_t__ asprintf (char**,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_stream (struct stream*) ; 
 struct stream* stream_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__**) ; 

int RarParse(struct stream *s, int *count, rar_file_t ***file)
{
    *count = 0;
    *file = NULL;

    const rar_pattern_t *pattern = FindVolumePattern(s->url);
    int volume_offset = 0;

    char *volume_mrl;
    if (asprintf(&volume_mrl, "%s", s->url) < 0)
        return -1;

    struct stream *vol = s;
    for (;;) {
        /* Skip marker & archive */
        if (IgnoreBlock(vol, RAR_BLOCK_MARKER) ||
            IgnoreBlock(vol, RAR_BLOCK_ARCHIVE)) {
            if (vol != s)
                free_stream(vol);
            free(volume_mrl);
            return -1;
        }

        /* */
        int has_next = -1;
        for (;;) {
            rar_block_t bk;
            int ret;

            if (PeekBlock(vol, &bk))
                break;

            switch(bk.type) {
            case RAR_BLOCK_END:
                ret = SkipEnd(vol, &bk);
                has_next = ret && (bk.flags & RAR_BLOCK_END_HAS_NEXT);
                break;
            case RAR_BLOCK_FILE:
                ret = SkipFile(vol, count, file, &bk, volume_mrl);
                break;
            default:
                ret = SkipBlock(vol, &bk);
                break;
            }
            if (ret)
                break;
        }
        if (has_next < 0 && *count > 0 && !(*file)[*count -1]->is_complete)
            has_next = 1;
        if (vol != s)
            free_stream(vol);

        if (!has_next || !pattern)
            goto done;

        /* Open next volume */
        const int volume_index = pattern->start + volume_offset++;
        if (volume_index > pattern->stop)
            goto done;

        char *volume_base;
        if (asprintf(&volume_base, "%.*s",
                     (int)(strlen(s->url) - strlen(pattern->match)), s->url) < 0) {
            goto done;
        }

        free(volume_mrl);
        if (pattern->start) {
            if (asprintf(&volume_mrl, pattern->format, volume_base, volume_index) < 0)
                volume_mrl = NULL;
        } else {
            if (asprintf(&volume_mrl, pattern->format, volume_base,
                         'r' + volume_index / 100, volume_index % 100) < 0)
                volume_mrl = NULL;
        }
        free(volume_base);

        if (!volume_mrl)
            goto done;

        vol = stream_create(volume_mrl, STREAM_READ, s->cancel, s->global);

        if (!vol)
            goto done;
    }

done:
    free(volume_mrl);
    if (*count == 0) {
        talloc_free(*file);
        return -1;
    }
    return 0;
}