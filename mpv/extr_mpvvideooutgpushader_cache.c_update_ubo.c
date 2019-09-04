#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dim_m; } ;
struct ra_layout {scalar_t__ stride; } ;
struct sc_uniform {size_t offset; TYPE_2__ input; struct ra_layout layout; int /*<<< orphan*/  v; } ;
struct ra_buf {int dummy; } ;
struct ra {TYPE_1__* fns; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* buf_update ) (struct ra*,struct ra_buf*,size_t,void*,scalar_t__) ;} ;

/* Variables and functions */
 struct ra_layout ra_renderpass_input_layout (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct ra*,struct ra_buf*,size_t,void*,scalar_t__) ; 

__attribute__((used)) static void update_ubo(struct ra *ra, struct ra_buf *ubo, struct sc_uniform *u)
{
    uintptr_t src = (uintptr_t) &u->v;
    size_t dst = u->offset;
    struct ra_layout src_layout = ra_renderpass_input_layout(&u->input);
    struct ra_layout dst_layout = u->layout;

    for (int i = 0; i < u->input.dim_m; i++) {
        ra->fns->buf_update(ra, ubo, dst, (void *)src, src_layout.stride);
        src += src_layout.stride;
        dst += dst_layout.stride;
    }
}