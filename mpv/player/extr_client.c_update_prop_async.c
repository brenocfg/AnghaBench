#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union m_option_value {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  uint64_t ;
struct observe_property {int async_updating; int async_value_valid; int changed; int /*<<< orphan*/  async_value_ts; TYPE_2__* type; int /*<<< orphan*/  async_value; int /*<<< orphan*/  format; int /*<<< orphan*/  name; int /*<<< orphan*/  async_change_ts; struct mpv_handle* owner; } ;
struct mpv_handle {int async_counter; int /*<<< orphan*/  lock; scalar_t__ lowest_changed; int /*<<< orphan*/  mpctx; } ;
struct getproperty_request {scalar_t__ status; union m_option_value* data; int /*<<< orphan*/  format; int /*<<< orphan*/  name; int /*<<< orphan*/  mpctx; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getproperty_fn (struct getproperty_request*) ; 
 int /*<<< orphan*/  m_option_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union m_option_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_client (struct mpv_handle*) ; 

__attribute__((used)) static void update_prop_async(void *p)
{
    struct observe_property *prop = p;
    struct mpv_handle *ctx = prop->owner;

    union m_option_value val = {0};
    bool val_valid = false;
    uint64_t value_ts;

    pthread_mutex_lock(&ctx->lock);
    value_ts = prop->async_change_ts;
    assert(prop->async_updating);
    pthread_mutex_unlock(&ctx->lock);

    struct getproperty_request req = {
        .mpctx = ctx->mpctx,
        .name = prop->name,
        .format = prop->format,
        .data = &val,
    };
    getproperty_fn(&req);
    val_valid = req.status >= 0;

    pthread_mutex_lock(&ctx->lock);

    assert(prop->async_updating);

    // Move to prop->async_value
    m_option_free(prop->type, &prop->async_value);
    memcpy(&prop->async_value, &val, prop->type->type->size);
    prop->async_value_valid = val_valid;

    prop->async_value_ts = value_ts;
    prop->async_updating = false;

    // Cause it to re-check the property.
    prop->changed = true;
    ctx->lowest_changed = 0;

    ctx->async_counter -= 1;
    wakeup_client(ctx);

    pthread_mutex_unlock(&ctx->lock);
}