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
struct mp_zimg_context {int /*<<< orphan*/  zimg_dst; int /*<<< orphan*/  zimg_src; int /*<<< orphan*/ * zimg_graph; int /*<<< orphan*/ * zimg_tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zimg_filter_graph_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_zimg(struct mp_zimg_context *ctx)
{
    free(ctx->zimg_tmp);
    ctx->zimg_tmp = NULL;
    zimg_filter_graph_free(ctx->zimg_graph);
    ctx->zimg_graph = NULL;
    TA_FREEP(&ctx->zimg_src);
    TA_FREEP(&ctx->zimg_dst);
}