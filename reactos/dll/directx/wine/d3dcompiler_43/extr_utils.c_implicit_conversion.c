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
struct hlsl_type {int dummy; } ;
struct hlsl_ir_node {int /*<<< orphan*/  data_type; } ;
struct TYPE_2__ {struct hlsl_ir_node node; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ compare_hlsl_types (int /*<<< orphan*/ ,struct hlsl_type*) ; 
 int /*<<< orphan*/  debug_hlsl_type (struct hlsl_type*) ; 
 TYPE_1__* new_cast (struct hlsl_ir_node*,struct hlsl_type*,struct source_location*) ; 

__attribute__((used)) static struct hlsl_ir_node *implicit_conversion(struct hlsl_ir_node *node, struct hlsl_type *type,
        struct source_location *loc)
{
    if (compare_hlsl_types(node->data_type, type))
        return node;
    TRACE("Implicit conversion of expression to %s\n", debug_hlsl_type(type));
    return &new_cast(node, type, loc)->node;
}