#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  RAnalReilArgType ;
typedef  TYPE_1__ RAnalReilArg ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_str_ncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reil_get_arg_type (int /*<<< orphan*/ *,char*) ; 

void reil_make_arg(RAnalEsil *esil, RAnalReilArg *arg, char *name) {
	if (!arg) {
		return;
	}
	RAnalReilArgType type = reil_get_arg_type (esil, name);
	arg->size = 0;
	arg->type = type;
	r_str_ncpy  (arg->name, name, sizeof (arg->name) - 1);
}