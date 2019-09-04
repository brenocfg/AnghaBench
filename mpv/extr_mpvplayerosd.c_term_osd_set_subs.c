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
struct MPContext {char* term_osd_subs; scalar_t__ video_out; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (struct MPContext*,char const*) ; 
 int /*<<< orphan*/  term_osd_update (struct MPContext*) ; 

void term_osd_set_subs(struct MPContext *mpctx, const char *text)
{
    if (mpctx->video_out || !text)
        text = ""; // disable
    if (strcmp(mpctx->term_osd_subs ? mpctx->term_osd_subs : "", text) == 0)
        return;
    talloc_free(mpctx->term_osd_subs);
    mpctx->term_osd_subs = talloc_strdup(mpctx, text);
    term_osd_update(mpctx);
}