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
struct TYPE_4__ {int amount_of_read_chars; int buff_for_parsing; } ;
typedef  TYPE_1__ SStateInfo ;
typedef  int EDemanglerErr ;

/* Variables and functions */
 int atoi (char*) ; 
 int eDemanglerErrOK ; 
 int eDemanglerErrUncorrectMangledSymbol ; 
 int eDemanglerErrUnsupportedMangling ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_num (TYPE_1__*) ; 
 int /*<<< orphan*/  init_state_struct (TYPE_1__*,char*) ; 
 char* r_str_newf (char*,...) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int get_template_params(char *sym, unsigned int *amount_of_read_chars, char **str_type_code) {
	EDemanglerErr err = eDemanglerErrOK;
	SStateInfo state;
	init_state_struct (&state, sym);
	const char template_param[] = "template-parameter-";
	char *tmp, *res = NULL;
	if (!strncmp (sym, "?", 1)) {
		// anonymous template param
		state.amount_of_read_chars += 1;
		state.buff_for_parsing += 1;
		res = get_num (&state);
		if (res) {
			tmp = r_str_newf("%s%s", template_param, res);
			free (res);
			res = tmp;
		}
	} else {
		if (strncmp (sym, "$", 1)) {
			err = eDemanglerErrUncorrectMangledSymbol;
			goto get_template_params_err;
		}
		sym++;
		state.amount_of_read_chars += 2;
		state.buff_for_parsing += 2;
		if (!strncmp (sym, "0", 1)) {
			// Signed integer
			tmp = get_num (&state);
			if (tmp) {
				int signed_a = atoi (tmp);
				res = r_str_newf ("%d", signed_a);
				free (tmp);
			}
		} else if (!strncmp (sym, "2", 1)) {
			// real value a ^ b
			char *a = get_num (&state);
			char *b = get_num (&state);
			if (a && b) {
				int signed_b = atoi (b);
				res = r_str_newf ("%sE%d", a, signed_b);
			}
			free (a);
			free (b);
		} else if (!strncmp (sym, "D", 1)) {
			// anonymous template param
			res = get_num (&state);
			if (res) {
				tmp = r_str_newf("%s%s", template_param, res);
				free (res);
				res = tmp;
			}
		} else if (!strncmp (sym, "F", 1)) {
			// Signed {a, b}
			char *a = get_num (&state);
			char *b = get_num (&state);
			if (a && b) {
				int signed_a = atoi (a);
				int signed_b = atoi (b);
				res = r_str_newf ("{%d, %d}", signed_a, signed_b);
			}
			free (a);
			free (b);
		} else if (!strncmp (sym, "G", 1)) {
			// Signed {a, b, c}
			char *a = get_num (&state);
			char *b = get_num (&state);
			char *c = get_num (&state);
			if (a && b && c) {
				int signed_a = atoi (a);
				int signed_b = atoi (b);
				int signed_c = atoi (c);
				res = r_str_newf ("{%d, %d, %d}", signed_a, signed_b, signed_c);
			}
			free (a);
			free (b);
			free (c);
		} else if (!strncmp (sym, "H", 1)) {
			// Unsigned integer
			res = get_num (&state);
		} else if (!strncmp (sym, "I", 1)) {
			// Unsigned {x, y}
			char *a = get_num (&state);
			char *b = get_num (&state);
			if (a && b) {
				res = r_str_newf ("{%s, %s}", a, b);
			}
			free (a);
			free (b);
		} else if (!strncmp (sym, "J", 1)) {
			// Unsigned {x, y, z}
			char *a = get_num (&state);
			char *b = get_num (&state);
			char *c = get_num (&state);
			if (a && b && c) {
				res = r_str_newf ("{%s, %s, %s}", a, b, c);
			}
			free (a);
			free (b);
			free (c);
		} else if (!strncmp (sym, "Q", 1)) {
			// anonymous non-type template parameter
			res = get_num (&state);
			if (res) {
				tmp = r_str_newf("non-type-%s%s", template_param, res);
				free (res);
				res = tmp;
			}
		}
	}

	if (!res) {
		err = eDemanglerErrUnsupportedMangling;
		goto get_template_params_err;
	}

	*str_type_code = res;
	*amount_of_read_chars = state.amount_of_read_chars;

get_template_params_err:
	return err;
}