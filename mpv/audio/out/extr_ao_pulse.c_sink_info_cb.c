#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sink_cb_ctx {TYPE_3__* ao; int /*<<< orphan*/  list; } ;
struct priv {int /*<<< orphan*/  mainloop; } ;
struct ao_device_desc {int /*<<< orphan*/  desc; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  description; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ pa_sink_info ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_5__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_device_list_add (int /*<<< orphan*/ ,TYPE_3__*,struct ao_device_desc*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sink_info_cb(pa_context *c, const pa_sink_info *i, int eol, void *ud)
{
    struct sink_cb_ctx *ctx = ud;
    struct priv *priv = ctx->ao->priv;

    if (eol) {
        pa_threaded_mainloop_signal(priv->mainloop, 0); // wakeup waitop()
        return;
    }

    struct ao_device_desc entry = {.name = i->name, .desc = i->description};
    ao_device_list_add(ctx->list, ctx->ao, &entry);
}