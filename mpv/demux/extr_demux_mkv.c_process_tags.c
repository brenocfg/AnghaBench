#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {struct mp_tags* tags; } ;
struct mp_tags {int dummy; } ;
struct mkv_demuxer {int num_tracks; TYPE_3__** tracks; struct ebml_tags* tags; } ;
struct ebml_tags {int n_tag; struct ebml_tag* tag; } ;
struct TYPE_11__ {scalar_t__ target_chapter_uid; scalar_t__ target_edition_uid; scalar_t__ target_track_uid; scalar_t__ target_attachment_uid; } ;
struct ebml_tag {int n_simple_tag; TYPE_5__* simple_tag; TYPE_4__ targets; } ;
struct TYPE_13__ {int num_chapters; int num_editions; struct mp_tags* metadata; TYPE_2__* editions; TYPE_1__* chapters; struct mkv_demuxer* priv; } ;
typedef  TYPE_6__ demuxer_t ;
struct TYPE_12__ {scalar_t__ tag_string; scalar_t__ tag_name; } ;
struct TYPE_10__ {scalar_t__ uid; struct sh_stream* stream; } ;
struct TYPE_9__ {scalar_t__ demuxer_id; struct mp_tags* metadata; } ;
struct TYPE_8__ {scalar_t__ demuxer_id; struct mp_tags* metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_tags_set_str (struct mp_tags*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void process_tags(demuxer_t *demuxer)
{
    struct mkv_demuxer *mkv_d = demuxer->priv;
    struct ebml_tags *tags = mkv_d->tags;

    if (!tags)
        return;

    for (int i = 0; i < tags->n_tag; i++) {
        struct ebml_tag tag = tags->tag[i];
        struct mp_tags *dst = NULL;

        if (tag.targets.target_chapter_uid) {
            for (int n = 0; n < demuxer->num_chapters; n++) {
                if (demuxer->chapters[n].demuxer_id ==
                    tag.targets.target_chapter_uid)
                {
                    dst = demuxer->chapters[n].metadata;
                    break;
                }
            }
        } else if (tag.targets.target_edition_uid) {
            for (int n = 0; n < demuxer->num_editions; n++) {
                if (demuxer->editions[n].demuxer_id ==
                    tag.targets.target_edition_uid)
                {
                    dst = demuxer->editions[n].metadata;
                    break;
                }
            }
        } else if (tag.targets.target_track_uid) {
            for (int n = 0; n < mkv_d->num_tracks; n++) {
                if (mkv_d->tracks[n]->uid ==
                    tag.targets.target_track_uid)
                {
                    struct sh_stream *sh = mkv_d->tracks[n]->stream;
                    if (sh)
                        dst = sh->tags;
                    break;
                }
            }
        } else if (tag.targets.target_attachment_uid) {
            /* ignore */
        } else {
            dst = demuxer->metadata;
        }

        if (dst) {
            for (int j = 0; j < tag.n_simple_tag; j++) {
                if (tag.simple_tag[j].tag_name && tag.simple_tag[j].tag_string) {
                    mp_tags_set_str(dst, tag.simple_tag[j].tag_name,
                                         tag.simple_tag[j].tag_string);
                }
            }
        }
    }
}