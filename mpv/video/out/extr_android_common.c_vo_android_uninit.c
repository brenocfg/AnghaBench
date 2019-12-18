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
struct vo_android_state {scalar_t__ native_window; } ;
struct vo {struct vo_android_state* android; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANativeWindow_release (scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (struct vo_android_state*) ; 

void vo_android_uninit(struct vo *vo)
{
    struct vo_android_state *ctx = vo->android;
    if (!ctx)
        return;

    if (ctx->native_window)
        ANativeWindow_release(ctx->native_window);

    talloc_free(ctx);
    vo->android = NULL;
}