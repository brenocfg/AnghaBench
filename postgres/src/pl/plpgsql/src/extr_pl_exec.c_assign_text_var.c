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
typedef  int /*<<< orphan*/  PLpgSQL_var ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  assign_simple_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
assign_text_var(PLpgSQL_execstate *estate, PLpgSQL_var *var, const char *str)
{
	assign_simple_var(estate, var, CStringGetTextDatum(str), false, true);
}