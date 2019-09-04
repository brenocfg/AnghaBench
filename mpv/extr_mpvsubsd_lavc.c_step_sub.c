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
struct seekpoint {double pts; double endpts; } ;
struct sd_lavc_priv {scalar_t__ num_seekpoints; struct seekpoint* seekpoints; } ;
struct sd {struct sd_lavc_priv* priv; } ;

/* Variables and functions */
 double INFINITY ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  compare_seekpoint ; 
 int /*<<< orphan*/  qsort (struct seekpoint*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double step_sub(struct sd *sd, double now, int movement)
{
    struct sd_lavc_priv *priv = sd->priv;
    int best = -1;
    double target = now;
    int direction = (movement > 0 ? 1 : -1) * !!movement;

    if (priv->num_seekpoints == 0)
        return MP_NOPTS_VALUE;

    qsort(priv->seekpoints, priv->num_seekpoints, sizeof(priv->seekpoints[0]),
          compare_seekpoint);

    do {
        int closest = -1;
        double closest_time = 0;
        for (int i = 0; i < priv->num_seekpoints; i++) {
            struct seekpoint *p = &priv->seekpoints[i];
            double start = p->pts;
            if (direction < 0) {
                double end = p->endpts == MP_NOPTS_VALUE ? INFINITY : p->endpts;
                if (end < target) {
                    if (closest < 0 || end > closest_time) {
                        closest = i;
                        closest_time = end;
                    }
                }
            } else if (direction > 0) {
                if (start > target) {
                    if (closest < 0 || start < closest_time) {
                        closest = i;
                        closest_time = start;
                    }
                }
            } else {
                if (start < target) {
                    if (closest < 0 || start >= closest_time) {
                        closest = i;
                        closest_time = start;
                    }
                }
            }
        }
        if (closest < 0)
            break;
        target = closest_time + direction;
        best = closest;
        movement -= direction;
    } while (movement);

    return best < 0 ? now : priv->seekpoints[best].pts;
}