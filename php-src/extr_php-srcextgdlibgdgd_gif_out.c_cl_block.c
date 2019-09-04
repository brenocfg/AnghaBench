#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  count_int ;
typedef  int /*<<< orphan*/  code_int ;
struct TYPE_5__ {int clear_flg; scalar_t__ ClearCode; scalar_t__ free_ent; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 int /*<<< orphan*/  cl_hash (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ hsize ; 
 int /*<<< orphan*/  output (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
cl_block (GifCtx *ctx)             /* table clear for block compress */
{

        cl_hash ( (count_int) hsize, ctx );
        ctx->free_ent = ctx->ClearCode + 2;
        ctx->clear_flg = 1;

        output( (code_int)ctx->ClearCode, ctx);
}