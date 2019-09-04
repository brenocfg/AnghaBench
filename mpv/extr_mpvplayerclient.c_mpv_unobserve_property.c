#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct observe_property {scalar_t__ reply_id; int dead; int /*<<< orphan*/  event_mask; scalar_t__ updating; } ;
struct TYPE_4__ {int num_properties; int /*<<< orphan*/  lock; scalar_t__ lowest_changed; int /*<<< orphan*/  property_event_masks; struct observe_property** properties; int /*<<< orphan*/  cur_event; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct observe_property**,int,int) ; 
 int /*<<< orphan*/  invalidate_global_event_mask (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_steal (int /*<<< orphan*/ ,struct observe_property*) ; 

int mpv_unobserve_property(mpv_handle *ctx, uint64_t userdata)
{
    pthread_mutex_lock(&ctx->lock);
    ctx->property_event_masks = 0;
    int count = 0;
    for (int n = ctx->num_properties - 1; n >= 0; n--) {
        struct observe_property *prop = ctx->properties[n];
        if (prop->reply_id == userdata) {
            if (prop->updating) {
                prop->dead = true;
            } else {
                // In case mpv_unobserve_property() is called after mpv_wait_event()
                // returned, and the mpv_event still references the name somehow,
                // make sure it's not freed while in use. The same can happen
                // with the value update mechanism.
                talloc_steal(ctx->cur_event, prop);
            }
            MP_TARRAY_REMOVE_AT(ctx->properties, ctx->num_properties, n);
            count++;
        }
        if (!prop->dead)
            ctx->property_event_masks |= prop->event_mask;
    }
    ctx->lowest_changed = 0;
    pthread_mutex_unlock(&ctx->lock);
    invalidate_global_event_mask(ctx);
    return count;
}