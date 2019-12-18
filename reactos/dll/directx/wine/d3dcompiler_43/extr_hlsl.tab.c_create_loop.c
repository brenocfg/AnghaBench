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
struct source_location {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; struct source_location loc; int /*<<< orphan*/  type; } ;
struct list {struct list* body; TYPE_1__ node; } ;
struct hlsl_ir_node {int /*<<< orphan*/  entry; } ;
struct hlsl_ir_loop {struct hlsl_ir_loop* body; TYPE_1__ node; } ;
struct hlsl_ir_if {struct hlsl_ir_if* body; TYPE_1__ node; } ;
typedef  enum loop_type { ____Placeholder_loop_type } loop_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HLSL_IR_LOOP ; 
 int LOOP_DO_WHILE ; 
 void* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  d3dcompiler_free (struct list*) ; 
 int /*<<< orphan*/  free_instr (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  free_instr_list (struct list*) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (struct list*) ; 
 int /*<<< orphan*/  list_move_head (struct list*,struct list*) ; 
 int /*<<< orphan*/  list_move_tail (struct list*,struct list*) ; 
 struct list* loop_condition (struct list*) ; 

__attribute__((used)) static struct list *create_loop(enum loop_type type, struct list *init, struct list *cond,
        struct hlsl_ir_node *iter, struct list *body, struct source_location *loc)
{
    struct list *list = NULL;
    struct hlsl_ir_loop *loop = NULL;
    struct hlsl_ir_if *cond_jump = NULL;

    list = d3dcompiler_alloc(sizeof(*list));
    if (!list)
        goto oom;
    list_init(list);

    if (init)
        list_move_head(list, init);

    loop = d3dcompiler_alloc(sizeof(*loop));
    if (!loop)
        goto oom;
    loop->node.type = HLSL_IR_LOOP;
    loop->node.loc = *loc;
    list_add_tail(list, &loop->node.entry);
    loop->body = d3dcompiler_alloc(sizeof(*loop->body));
    if (!loop->body)
        goto oom;
    list_init(loop->body);

    cond_jump = loop_condition(cond);
    if (!cond_jump)
        goto oom;

    if (type != LOOP_DO_WHILE)
        list_add_tail(loop->body, &cond_jump->node.entry);

    list_move_tail(loop->body, body);

    if (iter)
        list_add_tail(loop->body, &iter->entry);

    if (type == LOOP_DO_WHILE)
        list_add_tail(loop->body, &cond_jump->node.entry);

    d3dcompiler_free(init);
    d3dcompiler_free(cond);
    d3dcompiler_free(body);
    return list;

oom:
    ERR("Out of memory.\n");
    if (loop)
        d3dcompiler_free(loop->body);
    d3dcompiler_free(loop);
    d3dcompiler_free(cond_jump);
    d3dcompiler_free(list);
    free_instr_list(init);
    free_instr_list(cond);
    free_instr(iter);
    free_instr_list(body);
    return NULL;
}