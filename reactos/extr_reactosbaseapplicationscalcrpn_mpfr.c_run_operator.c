#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ calc_node_t ;
struct TYPE_9__ {scalar_t__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* op_i ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* op_f ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* op_p ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IDC_RADIO_DEC ; 
 int /*<<< orphan*/  apply_int_mask (int /*<<< orphan*/ *) ; 
 TYPE_6__ calc ; 
 TYPE_5__* operator_list ; 
 scalar_t__ percent_mode ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void run_operator(calc_node_t *result,
                  calc_node_t *a,
                  calc_node_t *b,
                  unsigned int operation)
{
    if (calc.base == IDC_RADIO_DEC) {
        if (percent_mode) {
            percent_mode = FALSE;
            operator_list[operation].op_p(&result->number, &a->number, &b->number);
        } else
            operator_list[operation].op_f(&result->number, &a->number, &b->number);
    } else {
        operator_list[operation].op_i(&result->number, &a->number, &b->number);
        /* apply final limiter to result */
        apply_int_mask(&result->number);
    }
}