#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * info_cb ;
struct TYPE_5__ {TYPE_1__* ctx; int /*<<< orphan*/ * info_callback; } ;
struct TYPE_4__ {int /*<<< orphan*/ * info_callback; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

__attribute__((used)) static info_cb get_callback(SSL *s)
{
    if (s->info_callback != NULL)
        return s->info_callback;
    else if (s->ctx->info_callback != NULL)
        return s->ctx->info_callback;

    return NULL;
}