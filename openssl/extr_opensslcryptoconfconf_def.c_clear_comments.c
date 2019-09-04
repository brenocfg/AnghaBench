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
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 scalar_t__ IS_COMMENT (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_DQUOTE (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_EOF (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_ESC (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_FCOMMENT (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_QUOTE (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  IS_WS (int /*<<< orphan*/ *,char) ; 
 char* scan_dquote (int /*<<< orphan*/ *,char*) ; 
 char* scan_esc (int /*<<< orphan*/ *,char*) ; 
 char* scan_quote (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void clear_comments(CONF *conf, char *p)
{
    for (;;) {
        if (IS_FCOMMENT(conf, *p)) {
            *p = '\0';
            return;
        }
        if (!IS_WS(conf, *p)) {
            break;
        }
        p++;
    }

    for (;;) {
        if (IS_COMMENT(conf, *p)) {
            *p = '\0';
            return;
        }
        if (IS_DQUOTE(conf, *p)) {
            p = scan_dquote(conf, p);
            continue;
        }
        if (IS_QUOTE(conf, *p)) {
            p = scan_quote(conf, p);
            continue;
        }
        if (IS_ESC(conf, *p)) {
            p = scan_esc(conf, p);
            continue;
        }
        if (IS_EOF(conf, *p))
            return;
        else
            p++;
    }
}