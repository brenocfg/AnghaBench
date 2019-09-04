#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tvi_handle_t ;
struct TYPE_4__ {char* device; char* adevice; } ;
typedef  TYPE_1__ tv_param_t ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  priv_t ;
struct TYPE_5__ {int video_fd; TYPE_1__* tv_param; void* video_dev; void* audio_dev; struct mp_log* log; } ;

/* Variables and functions */
 TYPE_3__* PRIV ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  functions ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  tv_free_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tv_new_handle (int,struct mp_log*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tvi_handle_t *tvi_init_v4l2(struct mp_log *log, tv_param_t* tv_param)
{
    tvi_handle_t *tvi_handle;

    tvi_handle = tv_new_handle(sizeof(priv_t), log, &functions);
    if (!tvi_handle) {
        return NULL;
    }
    PRIV->log = log;
    PRIV->video_fd = -1;

    PRIV->video_dev = strdup(tv_param->device? tv_param->device: "/dev/video0");
    if (!PRIV->video_dev) {
        tv_free_handle(tvi_handle);
        return NULL;
    }

    if (tv_param->adevice) {
        PRIV->audio_dev = strdup(tv_param->adevice);
        if (!PRIV->audio_dev) {
            free(PRIV->video_dev);
            tv_free_handle(tvi_handle);
            return NULL;
        }
    }

    PRIV->tv_param=tv_param;
    return tvi_handle;
}