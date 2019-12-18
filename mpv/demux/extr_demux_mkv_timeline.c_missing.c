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
struct tl_ctx {int num_sources; int /*<<< orphan*/ * sources; } ;

/* Variables and functions */

__attribute__((used)) static bool missing(struct tl_ctx *ctx)
{
    for (int i = 0; i < ctx->num_sources; i++) {
        if (!ctx->sources[i])
            return true;
    }
    return false;
}