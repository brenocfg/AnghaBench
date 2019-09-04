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
struct hlsl_scope {int /*<<< orphan*/  entry; struct hlsl_scope* upper; int /*<<< orphan*/  types; int /*<<< orphan*/  vars; } ;
struct hlsl_parse_ctx {int /*<<< orphan*/  scopes; struct hlsl_scope* cur_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  compare_hlsl_types_rb ; 
 struct hlsl_scope* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void push_scope(struct hlsl_parse_ctx *ctx)
{
    struct hlsl_scope *new_scope = d3dcompiler_alloc(sizeof(*new_scope));

    if (!new_scope)
    {
        ERR("Out of memory!\n");
        return;
    }
    TRACE("Pushing a new scope\n");
    list_init(&new_scope->vars);
    wine_rb_init(&new_scope->types, compare_hlsl_types_rb);
    new_scope->upper = ctx->cur_scope;
    ctx->cur_scope = new_scope;
    list_add_tail(&ctx->scopes, &new_scope->entry);
}