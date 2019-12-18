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
struct sub {double pts; double endpts; } ;
struct sd_times {double start; double end; } ;
struct sd_lavc_priv {int dummy; } ;
struct sd {struct sd_lavc_priv* priv; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 struct sub* get_current (struct sd_lavc_priv*,double) ; 

__attribute__((used)) static struct sd_times get_times(struct sd *sd, double pts)
{
    struct sd_lavc_priv *priv = sd->priv;
    struct sd_times res = { .start = MP_NOPTS_VALUE, .end = MP_NOPTS_VALUE };

    if (pts == MP_NOPTS_VALUE)
        return res;

    struct sub *current = get_current(priv, pts);

    if (!current)
        return res;

    res.start = current->pts;
    res.end = current->endpts;

    return res;
}