#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo {int dummy; } ;
struct TYPE_7__ {TYPE_4__* scaler; scalar_t__ interpolation; } ;
struct gl_video {TYPE_3__ opts; } ;
struct TYPE_5__ {double radius; } ;
struct filter_kernel {TYPE_1__ f; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {double radius; TYPE_2__ kernel; } ;

/* Variables and functions */
 size_t SCALER_TSCALE ; 
 scalar_t__ ceil (double) ; 
 int /*<<< orphan*/  gl_video_update_options (struct gl_video*) ; 
 struct filter_kernel* mp_find_filter_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_set_queue_params (struct vo*,int /*<<< orphan*/ ,int) ; 

void gl_video_configure_queue(struct gl_video *p, struct vo *vo)
{
    gl_video_update_options(p);

    int queue_size = 1;

    // Figure out an adequate size for the interpolation queue. The larger
    // the radius, the earlier we need to queue frames.
    if (p->opts.interpolation) {
        const struct filter_kernel *kernel =
            mp_find_filter_kernel(p->opts.scaler[SCALER_TSCALE].kernel.name);
        if (kernel) {
            // filter_scale wouldn't be correctly initialized were we to use it here.
            // This is fine since we're always upsampling, but beware if downsampling
            // is added!
            double radius = kernel->f.radius;
            radius = radius > 0 ? radius : p->opts.scaler[SCALER_TSCALE].radius;
            queue_size += 1 + ceil(radius);
        } else {
            // Oversample/linear case
            queue_size += 2;
        }
    }

    vo_set_queue_params(vo, 0, queue_size);
}