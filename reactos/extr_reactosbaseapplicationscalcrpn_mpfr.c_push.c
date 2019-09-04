#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mf; } ;
struct TYPE_10__ {int /*<<< orphan*/  operation; TYPE_1__ number; } ;
struct TYPE_11__ {struct TYPE_11__* next; TYPE_3__ node; } ;
typedef  TYPE_4__ stack_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  mf; } ;
struct TYPE_12__ {int /*<<< orphan*/  operation; TYPE_2__ number; } ;
typedef  TYPE_5__ calc_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mpfr_init_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* stack ; 

__attribute__((used)) static void push(calc_node_t *op)
{
    stack_node_t *z = (stack_node_t *)malloc(sizeof(stack_node_t));

    mpfr_init_set(z->node.number.mf, op->number.mf, MPFR_DEFAULT_RND);
    z->node.operation = op->operation;
    z->next = stack;
    stack = z;
}