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
struct demuxer {TYPE_1__* chapters; int /*<<< orphan*/  num_chapters; int /*<<< orphan*/  metadata; } ;
struct cue_track {int /*<<< orphan*/  tags; int /*<<< orphan*/  start; } ;
struct cue_file {int num_tracks; struct cue_track* tracks; } ;
struct TYPE_2__ {int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct demuxer*,char*) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int demuxer_add_chapter (struct demuxer*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp_check_embedded_cue (struct cue_file*) ; 
 struct cue_file* mp_parse_cue (int /*<<< orphan*/ ) ; 
 char* mp_tags_get_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_tags_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct cue_file*) ; 

__attribute__((used)) static void demux_init_cuesheet(struct demuxer *demuxer)
{
    char *cue = mp_tags_get_str(demuxer->metadata, "cuesheet");
    if (cue && !demuxer->num_chapters) {
        struct cue_file *f = mp_parse_cue(bstr0(cue));
        if (f) {
            if (mp_check_embedded_cue(f) < 0) {
                MP_WARN(demuxer, "Embedded cue sheet references more than one file. "
                        "Ignoring it.\n");
            } else {
                for (int n = 0; n < f->num_tracks; n++) {
                    struct cue_track *t = &f->tracks[n];
                    int idx = demuxer_add_chapter(demuxer, "", t->start, -1);
                    mp_tags_merge(demuxer->chapters[idx].metadata, t->tags);
                }
            }
        }
        talloc_free(f);
    }
}