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
struct ra_tex_download_params {int /*<<< orphan*/  stride; int /*<<< orphan*/  dst; TYPE_1__* tex; } ;
struct ra {int dummy; } ;
struct pl_tex_transfer_params {int /*<<< orphan*/  stride_w; int /*<<< orphan*/  ptr; struct pl_tex const* tex; } ;
struct pl_tex {int dummy; } ;
struct TYPE_2__ {struct pl_tex* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_gpu (struct ra*) ; 
 int pl_tex_download (int /*<<< orphan*/ ,struct pl_tex_transfer_params*) ; 
 int /*<<< orphan*/  texel_stride_w (int /*<<< orphan*/ ,struct pl_tex const*) ; 

__attribute__((used)) static bool tex_download_pl(struct ra *ra, struct ra_tex_download_params *params)
{
    const struct pl_tex *tex = params->tex->priv;
    struct pl_tex_transfer_params pl_params = {
        .tex = tex,
        .ptr = params->dst,
        .stride_w = texel_stride_w(params->stride, tex),
    };

    return pl_tex_download(get_gpu(ra), &pl_params);
}