#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demux_chapter {int dummy; } ;
struct TYPE_3__ {scalar_t__ num_chapters; int /*<<< orphan*/  chapters; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  chapter_compare ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void demuxer_sort_chapters(demuxer_t *demuxer)
{
    if (demuxer->num_chapters) {
        qsort(demuxer->chapters, demuxer->num_chapters,
            sizeof(struct demux_chapter), chapter_compare);
    }
}