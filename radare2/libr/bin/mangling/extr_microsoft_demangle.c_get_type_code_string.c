#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; int err; unsigned int amount_of_read_chars; } ;
struct TYPE_8__ {char* type_str; } ;
typedef  TYPE_1__ STypeCodeStr ;
typedef  TYPE_2__ SStateInfo ;
typedef  int /*<<< orphan*/  EDemanglerErr ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  eDemanglerErrMemoryAllocation ; 
 int /*<<< orphan*/  eDemanglerErrOK ; 
 int /*<<< orphan*/  eDemanglerErrUncorrectMangledSymbol ; 
 int /*<<< orphan*/  eDemanglerErrUnsupportedMangling ; 
 scalar_t__ eTCStateEnd ; 
 int eTCStateMachineErrOK ; 
#define  eTCStateMachineErrUncorrectTypeCode 129 
#define  eTCStateMachineErrUnsupportedTypeCode 128 
 int /*<<< orphan*/  free_type_code_str_struct (TYPE_1__*) ; 
 int /*<<< orphan*/  init_state_struct (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  init_type_code_str_struct (TYPE_1__*) ; 
 int /*<<< orphan*/  run_state (TYPE_2__*,TYPE_1__*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static EDemanglerErr get_type_code_string(char *sym, unsigned int *amount_of_read_chars, char **str_type_code) {
	EDemanglerErr err = eDemanglerErrOK;
	char *tmp_sym = strdup(sym);
	STypeCodeStr type_code_str;
	SStateInfo state;

	if (!init_type_code_str_struct(&type_code_str)) {
		err = eDemanglerErrMemoryAllocation;
		goto get_type_code_string_err;
	}

	init_state_struct (&state, tmp_sym);

	while (state.state != eTCStateEnd) {
		run_state (&state, &type_code_str);
		if (state.err != eTCStateMachineErrOK) {
			*str_type_code = NULL;
			*amount_of_read_chars = 0;
			switch (state.err) {
			case eTCStateMachineErrUncorrectTypeCode:
				err = eDemanglerErrUncorrectMangledSymbol;
				break;
			case eTCStateMachineErrUnsupportedTypeCode:
				err = eDemanglerErrUnsupportedMangling;
			default:
				break;
			}
			goto get_type_code_string_err;
		}
	}

	*str_type_code = strdup (type_code_str.type_str);
	*amount_of_read_chars = state.amount_of_read_chars;

get_type_code_string_err:
	R_FREE (tmp_sym);
	free_type_code_str_struct (&type_code_str);
	return err;
}