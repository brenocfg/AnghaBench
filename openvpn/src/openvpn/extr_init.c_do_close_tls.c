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
struct TYPE_2__ {scalar_t__ pulled_options_state; int /*<<< orphan*/ * options_string_remote; int /*<<< orphan*/ * options_string_local; int /*<<< orphan*/ * tls_multi; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_ctx_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  md_ctx_free (scalar_t__) ; 
 int /*<<< orphan*/  tls_multi_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
do_close_tls(struct context *c)
{
    if (c->c2.tls_multi)
    {
        tls_multi_free(c->c2.tls_multi, true);
        c->c2.tls_multi = NULL;
    }

#ifdef ENABLE_OCC
    /* free options compatibility strings */
    if (c->c2.options_string_local)
    {
        free(c->c2.options_string_local);
    }
    if (c->c2.options_string_remote)
    {
        free(c->c2.options_string_remote);
    }
    c->c2.options_string_local = c->c2.options_string_remote = NULL;
#endif

    if (c->c2.pulled_options_state)
    {
        md_ctx_cleanup(c->c2.pulled_options_state);
        md_ctx_free(c->c2.pulled_options_state);
    }
}