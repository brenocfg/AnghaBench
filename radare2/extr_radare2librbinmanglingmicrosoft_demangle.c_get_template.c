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
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  curr_pos; int /*<<< orphan*/  type_str; } ;
typedef  TYPE_1__ STypeCodeStr ;
typedef  TYPE_2__ SStrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  abbr_names ; 
 int /*<<< orphan*/  copy_string (TYPE_1__*,char*,int) ; 
 scalar_t__ eDemanglerErrOK ; 
 scalar_t__ get_type_code_string (char*,unsigned int*,char**) ; 
 int /*<<< orphan*/  init_type_code_str_struct (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_new () ; 
 char* strstr (char*,char*) ; 

int get_template (char *buf, SStrInfo *str_info) {
	int len = 0;
	unsigned int i = 0;
	char *str_type_code = NULL;
	char *tmp = strstr(buf, "@");
	STypeCodeStr type_code_str;
	// RListIter *it = NULL;
	// RList *saved_abbr_names = abbr_names;	// save current abbr names, this

	if (!tmp) {
		goto get_template_err;
	}
	if (!init_type_code_str_struct(&type_code_str)) {
		goto get_template_err;
	}
	abbr_names = r_list_new ();

	// get/copy template len/name
	len += (tmp - buf + 1);
	copy_string(&type_code_str, buf, len - 1);
	buf += len;

	if (*buf != '@') {
		copy_string(&type_code_str, "<", 0);
	}

	// get identifier
	while (*buf != '@') {
		if (i) {
			copy_string (&type_code_str, ", ", 0);
		}
		if (get_type_code_string (buf, &i, &str_type_code) != eDemanglerErrOK) {
			len = 0;
			goto get_template_err;
		}
		copy_string (&type_code_str, str_type_code, 0);
		buf += i;
		len += i;
		R_FREE (str_type_code);
	}
	if (*buf != '@') {
		len = 0;
		goto get_template_err;
	}
	copy_string (&type_code_str, ">", 0);
	buf++;
	len++;

	str_info->str_ptr = type_code_str.type_str;
	str_info->len = type_code_str.curr_pos;

get_template_err:
#if 0
	it = r_list_iterator (abbr_names);
	r_list_foreach (abbr_names, it, tmp) {
		R_FREE (tmp);
	}
	r_list_free (abbr_names);
	abbr_names = saved_abbr_names; // restore global list with name abbr.
#endif

	//    will be free at a caller function
	//    free_type_code_str_struct(&type_code_str);
	return len;
}