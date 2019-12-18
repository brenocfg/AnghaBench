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
struct ra_ctx {TYPE_1__* spirv; } ;
struct priv {int /*<<< orphan*/  compiler; int /*<<< orphan*/  opts; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  shaderc_compile_options_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shaderc_compiler_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shaderc_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->spirv->priv;
    if (!p)
        return;

    shaderc_compile_options_release(p->opts);
    shaderc_compiler_release(p->compiler);
}