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
struct ra_hwdec {struct priv* priv; } ;
struct priv {int renderer_enabled; int /*<<< orphan*/ * swpool; TYPE_1__* renderer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * input; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_component_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_renderer(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;

    if (p->renderer_enabled) {
        mmal_port_disable(p->renderer->control);
        mmal_port_disable(p->renderer->input[0]);

        mmal_port_flush(p->renderer->control);
        mmal_port_flush(p->renderer->input[0]);

        mmal_component_disable(p->renderer);
    }
    mmal_pool_destroy(p->swpool);
    p->swpool = NULL;
    p->renderer_enabled = false;
}