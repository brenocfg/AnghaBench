#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * sdb_types; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  cc_source; scalar_t__ c_type; int /*<<< orphan*/  fmt; scalar_t__ orig_c_type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ RAnalFuncArg ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  r_anal_cc_arg (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  r_type_func_args_name (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ r_type_func_args_type (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sdb_const_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* sdb_fmt (char*,scalar_t__) ; 
 int sdb_num_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,scalar_t__,int) ; 

__attribute__((used)) static void set_fcn_args_info(RAnalFuncArg *arg, RAnal *anal, const char *fcn_name, const char *cc, int arg_num) {
	if (!fcn_name || !arg || !anal) {
		return;
	}
	Sdb *TDB = anal->sdb_types;
	arg->name = r_type_func_args_name (TDB, fcn_name, arg_num);
	arg->orig_c_type = r_type_func_args_type (TDB, fcn_name, arg_num);
	if (!arg->name || !arg->orig_c_type) {
		eprintf ("Missing type for function argument (%s)\n", fcn_name);
		return;
	}
	if (!strncmp ("const ", arg->orig_c_type, 6)) {
		arg->c_type = arg->orig_c_type + 6;
	} else {
		arg->c_type = arg->orig_c_type;
	}
	const char *query = sdb_fmt ("type.%s", arg->c_type);
	arg->fmt = sdb_const_get (TDB, query, 0);
	const char *t_query = sdb_fmt ("type.%s.size", arg->c_type);
	arg->size = sdb_num_get (TDB, t_query, 0) / 8;
	arg->cc_source = r_anal_cc_arg (anal, cc, arg_num);
}