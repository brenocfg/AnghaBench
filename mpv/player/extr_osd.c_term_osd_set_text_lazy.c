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
struct MPContext {int /*<<< orphan*/  term_osd_text; TYPE_1__* opts; scalar_t__ video_out; } ;
struct TYPE_2__ {int term_osd; int /*<<< orphan*/  video_osd; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (struct MPContext*,char const*) ; 

__attribute__((used)) static void term_osd_set_text_lazy(struct MPContext *mpctx, const char *text)
{
    bool video_osd = mpctx->video_out && mpctx->opts->video_osd;
    if ((video_osd && mpctx->opts->term_osd != 1) || !text)
        text = ""; // disable
    talloc_free(mpctx->term_osd_text);
    mpctx->term_osd_text = talloc_strdup(mpctx, text);
}