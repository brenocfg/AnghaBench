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
struct ra_hwdec {struct priv* priv; } ;
struct priv {scalar_t__ renderer; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_renderer (struct ra_hwdec*) ; 
 int /*<<< orphan*/  mmal_component_release (scalar_t__) ; 
 int /*<<< orphan*/  mmal_vc_deinit () ; 

__attribute__((used)) static void destroy(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;

    disable_renderer(hw);

    if (p->renderer)
        mmal_component_release(p->renderer);

    mmal_vc_deinit();
}