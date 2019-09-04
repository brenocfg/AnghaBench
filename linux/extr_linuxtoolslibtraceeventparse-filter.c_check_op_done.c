#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * right; } ;
struct TYPE_5__ {int /*<<< orphan*/ * right; } ;
struct TYPE_4__ {int /*<<< orphan*/ * right; } ;
struct filter_arg {int type; TYPE_3__ num; TYPE_2__ op; TYPE_1__ exp; } ;

/* Variables and functions */
#define  FILTER_ARG_BOOLEAN 132 
#define  FILTER_ARG_EXP 131 
#define  FILTER_ARG_NUM 130 
#define  FILTER_ARG_OP 129 
#define  FILTER_ARG_STR 128 

__attribute__((used)) static int check_op_done(struct filter_arg *arg)
{
	switch (arg->type) {
	case FILTER_ARG_EXP:
		return arg->exp.right != NULL;

	case FILTER_ARG_OP:
		return arg->op.right != NULL;

	case FILTER_ARG_NUM:
		return arg->num.right != NULL;

	case FILTER_ARG_STR:
		/* A string conversion is always done */
		return 1;

	case FILTER_ARG_BOOLEAN:
		/* field not found, is ok */
		return 1;

	default:
		return 0;
	}
}