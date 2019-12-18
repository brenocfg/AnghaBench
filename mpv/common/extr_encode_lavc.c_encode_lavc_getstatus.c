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
struct encode_priv {double t0; double frames; double audioseconds; TYPE_1__* muxer; scalar_t__ failed; } ;
struct encode_lavc_context {int /*<<< orphan*/  lock; struct encode_priv* priv; } ;
struct TYPE_2__ {scalar_t__ pb; } ;

/* Variables and functions */
 float MPMAX (double,float) ; 
 double avio_size (scalar_t__) ; 
 double mp_time_sec () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

int encode_lavc_getstatus(struct encode_lavc_context *ctx,
                          char *buf, int bufsize,
                          float relative_position)
{
    if (!ctx)
        return -1;

    struct encode_priv *p = ctx->priv;

    double now = mp_time_sec();
    float minutes, megabytes, fps, x;
    float f = MPMAX(0.0001, relative_position);

    pthread_mutex_lock(&ctx->lock);

    if (p->failed) {
        snprintf(buf, bufsize, "(failed)\n");
        goto done;
    }

    minutes = (now - p->t0) / 60.0 * (1 - f) / f;
    megabytes = p->muxer->pb ? (avio_size(p->muxer->pb) / 1048576.0 / f) : 0;
    fps = p->frames / (now - p->t0);
    x = p->audioseconds / (now - p->t0);
    if (p->frames) {
        snprintf(buf, bufsize, "{%.1fmin %.1ffps %.1fMB}",
                 minutes, fps, megabytes);
    } else if (p->audioseconds) {
        snprintf(buf, bufsize, "{%.1fmin %.2fx %.1fMB}",
                 minutes, x, megabytes);
    } else {
        snprintf(buf, bufsize, "{%.1fmin %.1fMB}",
                 minutes, megabytes);
    }
    buf[bufsize - 1] = 0;

done:
    pthread_mutex_unlock(&ctx->lock);
    return 0;
}