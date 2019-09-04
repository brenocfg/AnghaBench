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
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_image {struct image_flags* priv; } ;
struct image_flags {int referenced; int pool_alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pool_lock () ; 
 int /*<<< orphan*/  pool_unlock () ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

__attribute__((used)) static void unref_image(void *opaque, uint8_t *data)
{
    struct mp_image *img = opaque;
    struct image_flags *it = img->priv;
    bool alive;
    pool_lock();
    assert(it->referenced);
    it->referenced = false;
    alive = it->pool_alive;
    pool_unlock();
    if (!alive)
        talloc_free(img);
}