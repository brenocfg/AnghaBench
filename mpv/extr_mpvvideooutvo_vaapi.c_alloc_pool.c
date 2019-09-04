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
struct pool_alloc_ctx {int /*<<< orphan*/  rt_format; int /*<<< orphan*/  vaapi; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int IMGFMT_VAAPI ; 
 struct mp_image* alloc_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct mp_image *alloc_pool(void *pctx, int fmt, int w, int h)
{
    struct pool_alloc_ctx *alloc_ctx = pctx;
    if (fmt != IMGFMT_VAAPI)
        return NULL;

    return alloc_surface(alloc_ctx->vaapi, alloc_ctx->rt_format, w, h);
}