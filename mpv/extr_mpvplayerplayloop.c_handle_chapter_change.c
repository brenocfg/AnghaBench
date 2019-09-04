#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct MPContext {int last_chapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_CHAPTER_CHANGE ; 
 int get_current_chapter (struct MPContext*) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_chapter_change(struct MPContext *mpctx)
{
    int chapter = get_current_chapter(mpctx);
    if (chapter != mpctx->last_chapter) {
        mpctx->last_chapter = chapter;
        mp_notify(mpctx, MPV_EVENT_CHAPTER_CHANGE, NULL);
    }
}