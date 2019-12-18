#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t found_varno; scalar_t__* datums; } ;
typedef  int /*<<< orphan*/  PLpgSQL_var ;
typedef  TYPE_1__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  assign_simple_var (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
exec_set_found(PLpgSQL_execstate *estate, bool state)
{
	PLpgSQL_var *var;

	var = (PLpgSQL_var *) (estate->datums[estate->found_varno]);
	assign_simple_var(estate, var, BoolGetDatum(state), false, false);
}