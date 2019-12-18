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
struct sub {double pts; double endpts; int /*<<< orphan*/  valid; } ;
struct sd_lavc_priv {struct sub* subs; } ;

/* Variables and functions */
 int MAX_QUEUE ; 
 double MP_NOPTS_VALUE ; 

__attribute__((used)) static struct sub *get_current(struct sd_lavc_priv *priv, double pts)
{
    struct sub *current = NULL;
    for (int n = 0; n < MAX_QUEUE; n++) {
        struct sub *sub = &priv->subs[n];
        if (!sub->valid)
            continue;
        if (pts == MP_NOPTS_VALUE ||
            ((sub->pts == MP_NOPTS_VALUE || pts >= sub->pts) &&
             (sub->endpts == MP_NOPTS_VALUE || pts < sub->endpts)))
        {
            // Ignore "trailing" subtitles with unknown length after 1 minute.
            if (sub->endpts == MP_NOPTS_VALUE && pts >= sub->pts + 60)
                break;
            current = sub;
            break;
        }
    }
    return current;
}