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
struct buffer {int dummy; } ;

/* Variables and functions */
 char append (struct sd*,struct buffer*,char) ; 

__attribute__((used)) static void copy_ass(struct sd *sd, char **rpp, struct buffer *buf)
{
    char *rp = *rpp;

    while (rp[0] == '{') {
        while (*rp) {
            char tmp = append(sd, buf, rp[0]);
            rp++;
            if (tmp == '}')
                break;
        }
    }
    *rpp = rp;

    return;
}