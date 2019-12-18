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
struct TYPE_5__ {int /*<<< orphan*/  code_list; } ;
typedef  TYPE_1__ script_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_script (TYPE_1__*) ; 
 int /*<<< orphan*/  release_vbscode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbscode_t ; 

__attribute__((used)) static void destroy_script(script_ctx_t *ctx)
{
    while(!list_empty(&ctx->code_list))
        release_vbscode(LIST_ENTRY(list_head(&ctx->code_list), vbscode_t, entry));

    release_script(ctx);
    heap_free(ctx);
}