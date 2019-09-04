#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union m_option_value {int /*<<< orphan*/  member_0; } ;
struct observe_property {int updating; int new_value_valid; int user_value_valid; int changed; scalar_t__ dead; int /*<<< orphan*/  format; int /*<<< orphan*/  new_value; int /*<<< orphan*/  user_value; int /*<<< orphan*/  name; struct mpv_handle* client; } ;
struct mpv_handle {int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_event; int /*<<< orphan*/  properties_updating; int /*<<< orphan*/  mpctx; } ;
struct m_option {TYPE_1__* type; } ;
struct getproperty_request {scalar_t__ status; union m_option_value* data; int /*<<< orphan*/  format; int /*<<< orphan*/  name; int /*<<< orphan*/  mpctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  equal_mpv_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct m_option* get_mp_type_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getproperty_fn (struct getproperty_request*) ; 
 int /*<<< orphan*/  m_option_free (struct m_option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union m_option_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_steal (int /*<<< orphan*/ ,struct observe_property*) ; 
 int /*<<< orphan*/  wakeup_client (struct mpv_handle*) ; 

__attribute__((used)) static void update_prop(void *p)
{
    struct observe_property *prop = p;
    struct mpv_handle *ctx = prop->client;

    const struct m_option *type = get_mp_type_get(prop->format);
    union m_option_value val = {0};

    struct getproperty_request req = {
        .mpctx = ctx->mpctx,
        .name = prop->name,
        .format = prop->format,
        .data = &val,
    };

    getproperty_fn(&req);

    pthread_mutex_lock(&ctx->lock);
    ctx->properties_updating--;
    prop->updating = false;
    m_option_free(type, &prop->new_value);
    prop->new_value_valid = req.status >= 0;
    if (prop->new_value_valid)
        memcpy(&prop->new_value, &val, type->type->size);
    if (prop->user_value_valid != prop->new_value_valid) {
        prop->changed = true;
    } else if (prop->user_value_valid && prop->new_value_valid) {
        if (!equal_mpv_value(&prop->user_value, &prop->new_value, prop->format))
            prop->changed = true;
    }
    if (prop->dead)
        talloc_steal(ctx->cur_event, prop);
    wakeup_client(ctx);
    pthread_mutex_unlock(&ctx->lock);
}