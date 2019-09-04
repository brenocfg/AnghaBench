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
struct sd {int dummy; } ;
struct buffer {int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_ass (struct sd*,char**,struct buffer*) ; 

__attribute__((used)) static bool skip_bracketed(struct sd *sd, char **rpp, struct buffer *buf)
{
    char *rp = *rpp;
    int old_pos = buf->pos;

    rp++; // skip past '['
    // skip past valid data searching for ]
    while (*rp && rp[0] != ']') {
        if (rp[0] == '{') {
            copy_ass(sd, &rp, buf);
        } else {
            rp++;
        }
    }
    if (!*rp) {
        // ] was not found
        buf->pos = old_pos;
        return false;
    }
    rp++; // skip ]
    // skip trailing spaces
    while (rp[0] == ' ') {
        rp++;
    }
    *rpp = rp;

    return true;
}