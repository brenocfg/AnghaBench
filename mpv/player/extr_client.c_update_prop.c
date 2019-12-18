#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union m_option_value {int /*<<< orphan*/  member_0; } ;
struct observe_property {scalar_t__ async_change_ts; scalar_t__ async_value_ts; int async_updating; int async_value_valid; int value_valid; TYPE_4__* type; union m_option_value value; int /*<<< orphan*/  format; int /*<<< orphan*/  name; int /*<<< orphan*/  async_value; } ;
struct mpv_handle {int async_counter; int /*<<< orphan*/  lock; TYPE_2__* mpctx; TYPE_1__* clients; } ;
struct getproperty_request {scalar_t__ status; union m_option_value* data; int /*<<< orphan*/  format; int /*<<< orphan*/  name; TYPE_2__* mpctx; } ;
struct TYPE_9__ {TYPE_3__* type; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  dispatch; } ;
struct TYPE_6__ {int /*<<< orphan*/  uses_vo_libmpv; } ;

/* Variables and functions */
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equal_mpv_value (union m_option_value*,union m_option_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getproperty_fn ; 
 int /*<<< orphan*/  m_option_copy (TYPE_4__*,union m_option_value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_option_free (TYPE_4__*,union m_option_value*) ; 
 int /*<<< orphan*/  memcpy (union m_option_value*,union m_option_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  mp_dispatch_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct observe_property*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_locked (struct mpv_handle*,int /*<<< orphan*/ ,struct getproperty_request*) ; 
 int /*<<< orphan*/  update_prop_async ; 

__attribute__((used)) static bool update_prop(struct mpv_handle *ctx, struct observe_property *prop)
{
    if (!prop->type)
        return true;

    union m_option_value val = {0};
    bool val_valid = false;

    // With vo_libmpv, we can't lock the core for stupid reasons.
    // Yes, that's FUCKING HORRIBLE. On the other hand, might be useful for
    // true async. properties in the future.
    if (atomic_load_explicit(&ctx->clients->uses_vo_libmpv, memory_order_relaxed)) {
        if (prop->async_change_ts > prop->async_value_ts) {
            if (!prop->async_updating) {
                prop->async_updating = true;
                ctx->async_counter += 1;
                mp_dispatch_enqueue(ctx->mpctx->dispatch, update_prop_async, prop);
            }
            return false; // re-update later when the changed value comes in
        }

        m_option_copy(prop->type, &val, &prop->async_value);
        val_valid = prop->async_value_valid;
    } else {
        pthread_mutex_unlock(&ctx->lock);

        struct getproperty_request req = {
            .mpctx = ctx->mpctx,
            .name = prop->name,
            .format = prop->format,
            .data = &val,
        };
        run_locked(ctx, getproperty_fn, &req);
        val_valid = req.status >= 0;

        pthread_mutex_lock(&ctx->lock);
    }

    bool changed = prop->value_valid != val_valid;
    if (prop->value_valid && val_valid)
        changed = !equal_mpv_value(&prop->value, &val, prop->format);

    if (changed) {
        prop->value_valid = val_valid;
        if (val_valid) {
            // move val to prop->value
            m_option_free(prop->type, &prop->value);
            memcpy(&prop->value, &val, prop->type->type->size);
            val_valid = false;
        }
    }

    if (val_valid)
        m_option_free(prop->type, &val);

    return changed;
}