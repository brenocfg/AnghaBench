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
struct demuxer {int num_chapters; TYPE_1__* chapters; } ;
struct demux_chapter {double pts; int /*<<< orphan*/  metadata; } ;
struct TYPE_2__ {int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,struct demux_chapter*,int,struct demux_chapter) ; 
 double demuxer_chapter_time (struct demuxer*,int) ; 
 int /*<<< orphan*/  mp_tags_dup (struct demux_chapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_chapters(struct demux_chapter **chapters, int *num_chapters,
                          struct demuxer *src, double start, double len,
                          double dest_offset)
{
    for (int n = 0; n < src->num_chapters; n++) {
        double time = demuxer_chapter_time(src, n);
        if (time >= start && time <= start + len) {
            struct demux_chapter ch = {
                .pts = dest_offset + time - start,
                .metadata = mp_tags_dup(*chapters, src->chapters[n].metadata),
            };
            MP_TARRAY_APPEND(NULL, *chapters, *num_chapters, ch);
        }
    }
}