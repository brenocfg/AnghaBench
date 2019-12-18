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
struct TYPE_2__ {scalar_t__ hw_subfmt; } ;
struct priv {int require_filtering; int /*<<< orphan*/  queue; TYPE_1__ out_params; TYPE_1__ params; int /*<<< orphan*/  out_format; int /*<<< orphan*/  pool; } ;
struct mp_image {TYPE_1__ params; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_FORMAT_NV12 ; 
 scalar_t__ IMGFMT_NV12 ; 
 int /*<<< orphan*/  destroy_video_proc (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 struct mp_image* mp_image_new_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_can_output (int /*<<< orphan*/ ) ; 
 struct mp_image* mp_refqueue_execute_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_should_deint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_write_out_pin (int /*<<< orphan*/ ,struct mp_image*) ; 
 struct mp_image* render (struct mp_filter*) ; 

__attribute__((used)) static void vf_d3d11vpp_process(struct mp_filter *vf)
{
    struct priv *p = vf->priv;

    struct mp_image *in_fmt = mp_refqueue_execute_reinit(p->queue);
    if (in_fmt) {
        mp_image_pool_clear(p->pool);

        destroy_video_proc(vf);

        p->params = in_fmt->params;
        p->out_params = p->params;

        p->out_params.hw_subfmt = IMGFMT_NV12;
        p->out_format = DXGI_FORMAT_NV12;

        p->require_filtering = p->params.hw_subfmt != p->out_params.hw_subfmt;
    }

    if (!mp_refqueue_can_output(p->queue))
        return;

    if (!mp_refqueue_should_deint(p->queue) && !p->require_filtering) {
        // no filtering
        struct mp_image *in = mp_image_new_ref(mp_refqueue_get(p->queue, 0));
        if (!in) {
            mp_filter_internal_mark_failed(vf);
            return;
        }
        mp_refqueue_write_out_pin(p->queue, in);
    } else {
        mp_refqueue_write_out_pin(p->queue, render(vf));
    }
}