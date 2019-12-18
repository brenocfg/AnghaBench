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
struct MPContext {int num_chapters; int /*<<< orphan*/  last_chapter_seek; TYPE_1__* chapters; } ;
struct TYPE_2__ {double pts; } ;

/* Variables and functions */
 int MPMAX (int /*<<< orphan*/ ,int) ; 
 double get_current_time (struct MPContext*) ; 

int get_current_chapter(struct MPContext *mpctx)
{
    if (!mpctx->num_chapters)
        return -2;
    double current_pts = get_current_time(mpctx);
    int i;
    for (i = 0; i < mpctx->num_chapters; i++)
        if (current_pts < mpctx->chapters[i].pts)
            break;
    return MPMAX(mpctx->last_chapter_seek, i - 1);
}