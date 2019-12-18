#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h; int /*<<< orphan*/  w; } ;
struct mp_zimg_repack {int* zmask; TYPE_3__* tmp; TYPE_1__ fmt; int /*<<< orphan*/  zimgfmt; scalar_t__ pack; } ;
struct mp_zimg_context {int /*<<< orphan*/  zimg_graph; } ;
struct TYPE_6__ {int num_planes; int* ys; } ;
struct TYPE_7__ {TYPE_2__ fmt; } ;

/* Variables and functions */
 scalar_t__ MP_IS_POWER_OF_2 (int /*<<< orphan*/ ) ; 
 int ZIMG_BUFFER_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* mp_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  talloc_steal (struct mp_zimg_repack*,TYPE_3__*) ; 
 int zimg_filter_graph_get_input_buffering (int /*<<< orphan*/ ,unsigned int*) ; 
 int zimg_filter_graph_get_output_buffering (int /*<<< orphan*/ ,unsigned int*) ; 
 int zimg_select_buffer_mask (unsigned int) ; 

__attribute__((used)) static bool allocate_buffer(struct mp_zimg_context *ctx,
                            struct mp_zimg_repack *r)
{
    unsigned lines = 0;
    int err;
    if (r->pack) {
        err = zimg_filter_graph_get_output_buffering(ctx->zimg_graph, &lines);
    } else {
        err = zimg_filter_graph_get_input_buffering(ctx->zimg_graph, &lines);
    }

    if (err)
        return false;

    r->zmask[0] = zimg_select_buffer_mask(lines);

    // Either ZIMG_BUFFER_MAX, or a power-of-2 slice buffer.
    assert(r->zmask[0] == ZIMG_BUFFER_MAX || MP_IS_POWER_OF_2(r->zmask[0] + 1));

    int h = r->zmask[0] == ZIMG_BUFFER_MAX ? r->fmt.h : r->zmask[0] + 1;
    if (h >= r->fmt.h) {
        h = r->fmt.h;
        r->zmask[0] = ZIMG_BUFFER_MAX;
    }

    r->tmp = mp_image_alloc(r->zimgfmt, r->fmt.w, h);
    talloc_steal(r, r->tmp);

    if (r->tmp) {
        for (int n = 1; n < r->tmp->fmt.num_planes; n++) {
            r->zmask[n] = r->zmask[0];
            if (r->zmask[0] != ZIMG_BUFFER_MAX)
                r->zmask[n] = r->zmask[n] >> r->tmp->fmt.ys[n];
        }
    }

    return !!r->tmp;
}