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
struct MPContext {char* term_osd_subs; char* term_osd_text; char* term_osd_status; char* term_osd_contents; int /*<<< orphan*/  statusline; int /*<<< orphan*/  global; TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_terminal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_STATUS ; 
 char* join_lines (struct MPContext*,char**,int) ; 
 int /*<<< orphan*/  mp_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ mp_msg_has_status_line (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void term_osd_update(struct MPContext *mpctx)
{
    int num_parts = 0;
    char *parts[3] = {0};

    if (!mpctx->opts->use_terminal)
        return;

    if (mpctx->term_osd_subs && mpctx->term_osd_subs[0])
        parts[num_parts++] = mpctx->term_osd_subs;
    if (mpctx->term_osd_text && mpctx->term_osd_text[0])
        parts[num_parts++] = mpctx->term_osd_text;
    if (mpctx->term_osd_status && mpctx->term_osd_status[0])
        parts[num_parts++] = mpctx->term_osd_status;

    char *s = join_lines(mpctx, parts, num_parts);

    if (strcmp(mpctx->term_osd_contents, s) == 0 &&
        mp_msg_has_status_line(mpctx->global))
    {
        talloc_free(s);
    } else {
        talloc_free(mpctx->term_osd_contents);
        mpctx->term_osd_contents = s;
        mp_msg(mpctx->statusline, MSGL_STATUS, "%s", s);
    }
}