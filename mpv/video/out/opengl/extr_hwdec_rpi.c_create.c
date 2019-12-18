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
struct ra_hwdec {int /*<<< orphan*/  log; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  renderer; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 int /*<<< orphan*/  MP_FATAL (struct ra_hwdec*,char*) ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_vc_deinit () ; 
 scalar_t__ mmal_vc_init () ; 

__attribute__((used)) static int create(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;
    p->log = hw->log;

    bcm_host_init();

    if (mmal_vc_init()) {
        MP_FATAL(hw, "Could not initialize MMAL.\n");
        return -1;
    }

    if (mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &p->renderer))
    {
        MP_FATAL(hw, "Could not create MMAL renderer.\n");
        mmal_vc_deinit();
        return -1;
    }

    return 0;
}