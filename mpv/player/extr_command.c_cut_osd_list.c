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
struct MPContext {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 int MPMAX (int,int) ; 
 int count_lines (char*) ; 
 int /*<<< orphan*/  osd_get_text_size (int /*<<< orphan*/ ,int*,int*) ; 
 char* skip_n_lines (char*,int) ; 
 int strlen (char*) ; 
 char* talloc_asprintf_append_buffer (char*,char*,int,...) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *cut_osd_list(struct MPContext *mpctx, char *text, int pos)
{
    int screen_h, font_h;
    osd_get_text_size(mpctx->osd, &screen_h, &font_h);
    int max_lines = screen_h / MPMAX(font_h, 1) - 1;

    if (!text || max_lines < 5)
        return text;

    int count = count_lines(text);
    if (count <= max_lines)
        return text;

    char *new = talloc_strdup(NULL, "");

    int start = MPMAX(pos - max_lines / 2, 0);
    if (start == 1)
        start = 0; // avoid weird transition when pad_h becomes visible
    int pad_h = start > 0;

    int space = max_lines - pad_h - 1;
    int pad_t = count - start > space;
    if (!pad_t)
        start = count - space;

    if (pad_h) {
        new = talloc_asprintf_append_buffer(new, "\342\206\221 (%d hidden items)\n",
                                            start);
    }

    char *head = skip_n_lines(text, start);
    if (!head) {
        talloc_free(new);
        return text;
    }

    int lines_shown = max_lines - pad_h - pad_t;
    char *tail = skip_n_lines(head, lines_shown);
    new = talloc_asprintf_append_buffer(new, "%.*s",
                            (int)(tail ? tail - head : strlen(head)), head);
    if (pad_t) {
        new = talloc_asprintf_append_buffer(new, "\342\206\223 (%d hidden items)\n",
                                            count - start - lines_shown + 1);
    }

    talloc_free(text);
    return new;
}