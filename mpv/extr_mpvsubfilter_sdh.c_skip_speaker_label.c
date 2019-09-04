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
 int /*<<< orphan*/  append (struct sd*,struct buffer*,char) ; 
 int /*<<< orphan*/  copy_ass (struct sd*,char**,struct buffer*) ; 
 scalar_t__ mp_isalpha (char) ; 
 scalar_t__ mp_isdigit (char) ; 
 scalar_t__ mp_isupper (char) ; 

__attribute__((used)) static void skip_speaker_label(struct sd *sd, char **rpp, struct buffer *buf)
{
    int filter_harder = sd->opts->sub_filter_SDH_harder;
    char *rp = *rpp;
    int old_pos = buf->pos;

    copy_ass(sd, &rp, buf);
    // copy any leading "- "
    if (rp[0] == '-') {
        append(sd, buf, rp[0]);
        rp++;
    }
    copy_ass(sd, &rp, buf);
    while (rp[0] == ' ') {
        append(sd, buf, rp[0]);
        rp++;
        copy_ass(sd, &rp, buf);
    }
    // skip past valid data searching for :
    while (*rp && rp[0] != ':') {
        if (rp[0] == '{') {
            copy_ass(sd, &rp, buf);
        } else if ((mp_isalpha(rp[0]) &&
                    (filter_harder || mp_isupper(rp[0]) || rp[0] == 'l')) ||
                   mp_isdigit(rp[0]) ||
                   rp[0] == ' ' || rp[0] == '\'' ||
                   (filter_harder && (rp[0] == '(' || rp[0] == ')')) ||
                   rp[0] == '#' || rp[0] == '.' || rp[0] == ',') {
            rp++;
        } else {
            buf->pos = old_pos;
            return;
         }
    }
    if (!*rp) {
        // : was not found
        buf->pos = old_pos;
        return;
    }
    rp++; // skip :
    copy_ass(sd, &rp, buf);
    if (!*rp) {
        // end of data
    } else if (rp[0] == '\\' && rp[1] == 'N') {
        // line end follows - skip it as line is empty
        rp += 2;
    } else if (rp[0] == ' ') {
        while (rp[0] == ' ') {
            rp++;
        }
        if (rp[0] == '\\' && rp[1] == 'N') {
            // line end follows - skip it as line is empty
            rp += 2;
        }
    } else {
        // non space follows - no speaker label
        buf->pos = old_pos;
        return;
    }
    *rpp = rp;

    return;
}