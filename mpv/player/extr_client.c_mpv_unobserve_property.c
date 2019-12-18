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
struct observe_property {scalar_t__ reply_id; int dead; } ;
struct TYPE_4__ {int num_properties; int /*<<< orphan*/  lock; struct observe_property** properties; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  mark_property_changed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int mpv_unobserve_property(mpv_handle *ctx, uint64_t userdata)
{
    pthread_mutex_lock(&ctx->lock);
    int count = 0;
    for (int n = 0; n < ctx->num_properties; n++) {
        struct observe_property *prop = ctx->properties[n];
        // Perform actual removal of the property lazily to avoid creating
        // dangling pointers and such.
        if (prop->reply_id == userdata && !prop->dead) {
            mark_property_changed(ctx, n);
            prop->dead = true;
            count++;
        }
    }
    pthread_mutex_unlock(&ctx->lock);
    return count;
}