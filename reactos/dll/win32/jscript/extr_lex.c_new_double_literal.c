#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  dval; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ literal_t ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  LT_DOUBLE ; 
 TYPE_2__* parser_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static literal_t *new_double_literal(parser_ctx_t *ctx, DOUBLE d)
{
    literal_t *ret = parser_alloc(ctx, sizeof(literal_t));

    ret->type = LT_DOUBLE;
    ret->u.dval = d;
    return ret;
}