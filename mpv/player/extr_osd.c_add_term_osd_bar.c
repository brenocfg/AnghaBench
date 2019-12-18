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
struct MPOpts {int /*<<< orphan*/  term_osd_bar_chars; } ;
struct MPContext {struct MPOpts* opts; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 int MPCLAMP (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_split_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_current_pos_ratio (struct MPContext*,int) ; 
 int /*<<< orphan*/  saddf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_term_osd_bar(struct MPContext *mpctx, char **line, int width)
{
    struct MPOpts *opts = mpctx->opts;

    if (width < 5)
        return;

    int pos = get_current_pos_ratio(mpctx, false) * (width - 3);
    pos = MPCLAMP(pos, 0, width - 3);

    bstr chars = bstr0(opts->term_osd_bar_chars);
    bstr parts[5];
    for (int n = 0; n < 5; n++)
        parts[n] = bstr_split_utf8(chars, &chars);

    saddf(line, "\r%.*s", BSTR_P(parts[0]));
    for (int n = 0; n < pos; n++)
        saddf(line, "%.*s", BSTR_P(parts[1]));
    saddf(line, "%.*s", BSTR_P(parts[2]));
    for (int n = 0; n < width - 3 - pos; n++)
        saddf(line, "%.*s", BSTR_P(parts[3]));
    saddf(line, "%.*s", BSTR_P(parts[4]));
}