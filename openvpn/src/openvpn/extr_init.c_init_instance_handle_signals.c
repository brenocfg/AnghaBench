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
struct env_set {int dummy; } ;
struct context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SIG (struct context*) ; 
 int /*<<< orphan*/  init_instance (struct context*,struct env_set const*,unsigned int const) ; 
 int /*<<< orphan*/  post_init_signal_catch () ; 
 int /*<<< orphan*/  pre_init_signal_catch () ; 
 int /*<<< orphan*/  remap_signal (struct context*) ; 
 int /*<<< orphan*/  uninit_management_callback () ; 

void
init_instance_handle_signals(struct context *c, const struct env_set *env, const unsigned int flags)
{
    pre_init_signal_catch();
    init_instance(c, env, flags);
    post_init_signal_catch();

    /*
     * This is done so that signals thrown during
     * initialization can bring us back to
     * a management hold.
     */
    if (IS_SIG(c))
    {
        remap_signal(c);
        uninit_management_callback();
    }
}