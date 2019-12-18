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
struct mp_sws_context {int /*<<< orphan*/  dst_filter; int /*<<< orphan*/  src_filter; int /*<<< orphan*/  sws; } ;

/* Variables and functions */
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_freeFilter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mp_sws(void *p)
{
    struct mp_sws_context *ctx = p;
    sws_freeContext(ctx->sws);
    sws_freeFilter(ctx->src_filter);
    sws_freeFilter(ctx->dst_filter);
}