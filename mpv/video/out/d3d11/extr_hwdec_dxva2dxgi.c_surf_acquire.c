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
struct ra_hwdec_mapper {struct priv* priv; } ;
struct queue_surf {int dummy; } ;
struct priv {int queue_len; size_t queue_pos; struct queue_surf** queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct ra_hwdec_mapper*,char*,int) ; 
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct priv*,struct queue_surf**,int,size_t,struct queue_surf*) ; 
 int /*<<< orphan*/  MP_WARN (struct ra_hwdec_mapper*,char*) ; 
 struct queue_surf* surf_create (struct ra_hwdec_mapper*) ; 
 int /*<<< orphan*/  surf_is_idle11 (struct ra_hwdec_mapper*,struct queue_surf*) ; 
 int /*<<< orphan*/  surf_wait_idle11 (struct ra_hwdec_mapper*,struct queue_surf*) ; 

__attribute__((used)) static struct queue_surf *surf_acquire(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;

    if (!p->queue_len || !surf_is_idle11(mapper, p->queue[p->queue_pos])) {
        if (p->queue_len < 16) {
            struct queue_surf *surf = surf_create(mapper);
            if (!surf)
                return NULL;

            // The next surface is busy, so grow the queue
            MP_TARRAY_INSERT_AT(p, p->queue, p->queue_len, p->queue_pos, surf);
            MP_DBG(mapper, "Queue grew to %d surfaces\n", p->queue_len);
        } else {
            // For sanity, don't let the queue grow beyond 16 surfaces. It
            // should never get this big. If it does, wait for the surface to
            // become idle rather than polling it.
            if (!surf_wait_idle11(mapper, p->queue[p->queue_pos]))
                return NULL;
            MP_WARN(mapper, "Queue underflow!\n");
        }
    }
    return p->queue[p->queue_pos];
}