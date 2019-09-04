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
struct wine_rb_tree {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare_function_rb ; 
 TYPE_1__ hlsl_ctx ; 
 int /*<<< orphan*/  wine_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void init_functions_tree(struct wine_rb_tree *funcs)
{
    wine_rb_init(&hlsl_ctx.functions, compare_function_rb);
}