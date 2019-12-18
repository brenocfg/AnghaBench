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
struct MPContext {char* term_osd_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (struct MPContext*,char const*) ; 
 int /*<<< orphan*/  terminal_get_size (int*,int*) ; 

__attribute__((used)) static void term_osd_set_status_lazy(struct MPContext *mpctx, const char *text)
{
    talloc_free(mpctx->term_osd_status);
    mpctx->term_osd_status = talloc_strdup(mpctx, text);

    int w = 80, h = 24;
    terminal_get_size(&w, &h);
    if (strlen(mpctx->term_osd_status) > w && !strchr(mpctx->term_osd_status, '\n'))
        mpctx->term_osd_status[w] = '\0';
}