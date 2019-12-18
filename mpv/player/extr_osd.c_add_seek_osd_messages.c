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
struct MPContext {int add_osd_seek_info; int osd_show_pos; char* filename; TYPE_1__* opts; scalar_t__ video_out; } ;
struct TYPE_2__ {int term_osd; int /*<<< orphan*/  osd_duration; int /*<<< orphan*/  video_osd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCLAMP (double,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSD_BAR_SEEK ; 
 int OSD_SEEK_INFO_BAR ; 
 int OSD_SEEK_INFO_CHAPTER_TEXT ; 
 int OSD_SEEK_INFO_CURRENT_FILE ; 
 int OSD_SEEK_INFO_TEXT ; 
 char* chapter_display_name (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_chapter (struct MPContext*) ; 
 double get_current_pos_ratio (struct MPContext*,int) ; 
 int /*<<< orphan*/  set_osd_bar (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_osd_bar_chapters (struct MPContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_osd_msg (struct MPContext*,int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void add_seek_osd_messages(struct MPContext *mpctx)
{
    if (mpctx->add_osd_seek_info & OSD_SEEK_INFO_BAR) {
        double pos = get_current_pos_ratio(mpctx, false);
        set_osd_bar(mpctx, OSD_BAR_SEEK, 0, 1, 0, MPCLAMP(pos, 0, 1));
        set_osd_bar_chapters(mpctx, OSD_BAR_SEEK);
    }
    if (mpctx->add_osd_seek_info & OSD_SEEK_INFO_TEXT) {
        // Never in term-osd mode
        bool video_osd = mpctx->video_out && mpctx->opts->video_osd;
        if (video_osd && mpctx->opts->term_osd != 1) {
            if (set_osd_msg(mpctx, 1, mpctx->opts->osd_duration, ""))
                mpctx->osd_show_pos = true;
        }
    }
    if (mpctx->add_osd_seek_info & OSD_SEEK_INFO_CHAPTER_TEXT) {
        char *chapter = chapter_display_name(mpctx, get_current_chapter(mpctx));
        set_osd_msg(mpctx, 1, mpctx->opts->osd_duration,
                     "Chapter: %s", chapter);
        talloc_free(chapter);
    }
    if (mpctx->add_osd_seek_info & OSD_SEEK_INFO_CURRENT_FILE) {
        if (mpctx->filename) {
            set_osd_msg(mpctx, 1, mpctx->opts->osd_duration, "%s",
                        mpctx->filename);
        }
    }
    mpctx->add_osd_seek_info = 0;
}