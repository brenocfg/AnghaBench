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
struct vo {int /*<<< orphan*/  log; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;
struct priv {int /*<<< orphan*/  renderer; int /*<<< orphan*/  display_cond; int /*<<< orphan*/  display_mutex; TYPE_1__ egl; scalar_t__ layer; scalar_t__ osd_layer; scalar_t__ video_layer; scalar_t__ background_layer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_vc_init () ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ recreate_dispmanx (struct vo*) ; 
 int /*<<< orphan*/  tv_callback ; 
 int /*<<< orphan*/  uninit (struct vo*) ; 
 scalar_t__ update_display_size (struct vo*) ; 
 int /*<<< orphan*/  vc_tv_register_callback (int /*<<< orphan*/ ,struct vo*) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct priv *p = vo->priv;

    p->background_layer = p->layer;
    p->video_layer = p->layer + 1;
    p->osd_layer = p->layer + 2;

    p->egl.log = vo->log;

    bcm_host_init();

    if (mmal_vc_init()) {
        MP_FATAL(vo, "Could not initialize MMAL.\n");
        return -1;
    }

    pthread_mutex_init(&p->display_mutex, NULL);
    pthread_cond_init(&p->display_cond, NULL);

    if (recreate_dispmanx(vo) < 0)
        goto fail;

    if (update_display_size(vo) < 0)
        goto fail;

    if (mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &p->renderer))
    {
        MP_FATAL(vo, "Could not create MMAL renderer.\n");
        goto fail;
    }

    vc_tv_register_callback(tv_callback, vo);

    return 0;

fail:
    uninit(vo);
    return -1;
}