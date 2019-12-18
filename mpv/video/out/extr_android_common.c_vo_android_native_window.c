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
struct vo_android_state {int /*<<< orphan*/ * native_window; } ;
struct vo {struct vo_android_state* android; } ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */

ANativeWindow *vo_android_native_window(struct vo *vo)
{
    struct vo_android_state *ctx = vo->android;
    return ctx->native_window;
}