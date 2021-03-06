#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {TYPE_1__* _num; } ;
struct TYPE_8__ {TYPE_2__ val; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ DsoJsonObj ;

/* Variables and functions */
 TYPE_3__* dso_json_num_new () ; 

DsoJsonObj * dso_json_num_new_from_num (ut64 num) {
	DsoJsonObj *x = dso_json_num_new ();
	if (x) x->val._num->value = num;
	return x;
}