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
struct mp_image_pool {int num_images; struct mp_image** images; } ;
struct mp_image {struct image_flags* priv; } ;
struct image_flags {int pool_alive; int referenced; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pool_lock () ; 
 int /*<<< orphan*/  pool_unlock () ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

void mp_image_pool_clear(struct mp_image_pool *pool)
{
    for (int n = 0; n < pool->num_images; n++) {
        struct mp_image *img = pool->images[n];
        struct image_flags *it = img->priv;
        bool referenced;
        pool_lock();
        assert(it->pool_alive);
        it->pool_alive = false;
        referenced = it->referenced;
        pool_unlock();
        if (!referenced)
            talloc_free(img);
    }
    pool->num_images = 0;
}