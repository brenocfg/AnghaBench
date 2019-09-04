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
struct mp_image_pool {int fmt; int w; int h; int /*<<< orphan*/  allocator_ctx; struct mp_image* (* allocator ) (int /*<<< orphan*/ ,int,int,int) ;} ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 struct mp_image* mp_image_alloc (int,int,int) ; 
 int /*<<< orphan*/  mp_image_pool_add (struct mp_image_pool*,struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_pool_clear (struct mp_image_pool*) ; 
 struct mp_image* mp_image_pool_get_no_alloc (struct mp_image_pool*,int,int,int) ; 
 struct mp_image* stub1 (int /*<<< orphan*/ ,int,int,int) ; 

struct mp_image *mp_image_pool_get(struct mp_image_pool *pool, int fmt,
                                   int w, int h)
{
    if (!pool)
        return mp_image_alloc(fmt, w, h);
    struct mp_image *new = mp_image_pool_get_no_alloc(pool, fmt, w, h);
    if (!new) {
        if (fmt != pool->fmt || w != pool->w || h != pool->h)
            mp_image_pool_clear(pool);
        pool->fmt = fmt;
        pool->w = w;
        pool->h = h;
        if (pool->allocator) {
            new = pool->allocator(pool->allocator_ctx, fmt, w, h);
        } else {
            new = mp_image_alloc(fmt, w, h);
        }
        if (!new)
            return NULL;
        mp_image_pool_add(pool, new);
        new = mp_image_pool_get_no_alloc(pool, fmt, w, h);
    }
    return new;
}