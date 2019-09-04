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
struct sd {TYPE_1__* opts; } ;
struct buffer {int pos; } ;
struct TYPE_2__ {int sub_filter_SDH_harder; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_ass (struct sd*,char**,struct buffer*) ; 
 scalar_t__ mp_isalpha (char) ; 
 scalar_t__ mp_isdigit (char) ; 
 scalar_t__ mp_isupper (char) ; 

__attribute__((used)) static bool skip_parenthesed(struct sd *sd, char **rpp, struct buffer *buf)
{
    int filter_harder = sd->opts->sub_filter_SDH_harder;
    char *rp = *rpp;
    int old_pos = buf->pos;

    rp++; // skip past '('
    // skip past valid data searching for )
    bool only_digits = true;
    while (*rp && rp[0] != ')') {
        if (rp[0] == '{') {
            copy_ass(sd, &rp, buf);
        } else if ((mp_isalpha(rp[0]) &&
                    (filter_harder || mp_isupper(rp[0]) || rp[0] == 'l')) ||
                   mp_isdigit(rp[0]) ||
                   rp[0] == ' ' || rp[0] == '\'' || rp[0] == '#' ||
                   rp[0] == '.' || rp[0] == ',' ||
                   rp[0] == '-' || rp[0] == '"' || rp[0] == '\\') {
            if (!mp_isdigit(rp[0]))
                only_digits = false;
            rp++;
        } else {
            buf->pos = old_pos;
            return false;
        }
    }
    if (!*rp) {
        // ) was not found
        buf->pos = old_pos;
        return false;
    }
    if (only_digits) {
        // number within parentheses is probably not SDH
        buf->pos = old_pos;
        return false;
    }
    rp++; // skip )
    // skip trailing spaces
    while (rp[0] == ' ') {
        rp++;
    }
    *rpp = rp;

    return true;
}