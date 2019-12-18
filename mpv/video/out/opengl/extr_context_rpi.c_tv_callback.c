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
typedef  int /*<<< orphan*/  uint32_t ;
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  reload_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vo_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tv_callback(void *callback_data, uint32_t reason, uint32_t param1,
                        uint32_t param2)
{
    struct ra_ctx *ctx = callback_data;
    struct priv *p = ctx->priv;
    atomic_store(&p->reload_display, true);
    vo_wakeup(ctx->vo);
}