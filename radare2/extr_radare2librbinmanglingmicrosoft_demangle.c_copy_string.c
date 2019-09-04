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
struct TYPE_3__ {int type_str_len; int curr_pos; char* type_str; } ;
typedef  TYPE_1__ STypeCodeStr ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_str_ncpy (char*,char*,int) ; 
 scalar_t__ realloc (char*,int) ; 
 unsigned int strlen (char*) ; 

int copy_string(STypeCodeStr *type_code_str, char *str_for_copy, unsigned int copy_len) {
	int res = 1; // all is OK
	int str_for_copy_len = (copy_len == 0 && str_for_copy) ? strlen (str_for_copy) : copy_len;
	int free_space = type_code_str->type_str_len - type_code_str->curr_pos - 1;

	if (str_for_copy_len > free_space) {
		return 0;
	}
	if (free_space > str_for_copy_len) {
		int newlen = type_code_str->type_str_len + (str_for_copy_len << 1) + 1;
		if (newlen < 1) {
			R_FREE (type_code_str->type_str);
			goto copy_string_err;
		}
		type_code_str->type_str_len = newlen;
		char *type_str = (char *) realloc (type_code_str->type_str, newlen);
		if (!type_str) {
			R_FREE (type_code_str->type_str);
			goto copy_string_err;
		}
		type_code_str->type_str = type_str;
		if (!type_code_str->type_str) {
			res = 0;
			goto copy_string_err;
		}
	}

	char *dst = type_code_str->type_str + type_code_str->curr_pos;
	if (!dst) {
		return 0;
	}

	if (str_for_copy) {
		r_str_ncpy  (dst, str_for_copy, str_for_copy_len + 1);
	} else {
		memset (dst, 0, str_for_copy_len);
	}
	type_code_str->curr_pos += str_for_copy_len;
	if (type_code_str->type_str) {
		type_code_str->type_str[type_code_str->curr_pos] = '\0';
	}

copy_string_err:
	return res;
}