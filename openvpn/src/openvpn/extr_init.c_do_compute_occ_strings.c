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
struct gc_arena {int dummy; } ;
struct TYPE_4__ {void* options_string_remote; void* options_string_local; scalar_t__ tls_multi; int /*<<< orphan*/  frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  tuntap; } ;
struct context {TYPE_2__ c2; int /*<<< orphan*/  net_ctx; TYPE_1__ c1; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SHOW_OCC ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 void* options_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct gc_arena*) ; 
 int /*<<< orphan*/  options_string_version (void*,struct gc_arena*) ; 
 int /*<<< orphan*/  tls_multi_init_set_options (scalar_t__,void*,void*) ; 

__attribute__((used)) static void
do_compute_occ_strings(struct context *c)
{
    struct gc_arena gc = gc_new();

    c->c2.options_string_local =
        options_string(&c->options, &c->c2.frame, c->c1.tuntap, &c->net_ctx,
                       false, &gc);
    c->c2.options_string_remote =
        options_string(&c->options, &c->c2.frame, c->c1.tuntap, &c->net_ctx,
                       true, &gc);

    msg(D_SHOW_OCC, "Local Options String (VER=%s): '%s'",
        options_string_version(c->c2.options_string_local, &gc),
        c->c2.options_string_local);
    msg(D_SHOW_OCC, "Expected Remote Options String (VER=%s): '%s'",
        options_string_version(c->c2.options_string_remote, &gc),
        c->c2.options_string_remote);

    if (c->c2.tls_multi)
    {
        tls_multi_init_set_options(c->c2.tls_multi,
                                   c->c2.options_string_local,
                                   c->c2.options_string_remote);
    }

    gc_free(&gc);
}