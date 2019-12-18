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
struct MPContext {int num_chapters; TYPE_1__* chapters; } ;
struct TYPE_2__ {double pts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 

double chapter_start_time(struct MPContext *mpctx, int chapter)
{
    if (chapter == -1)
        return 0;
    if (chapter >= 0 && chapter < mpctx->num_chapters)
        return mpctx->chapters[chapter].pts;
    return MP_NOPTS_VALUE;
}