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
typedef  int ut32 ;

/* Variables and functions */
 char* malloc (int) ; 
 char* r_cmd_java_consumetok (char const*,char,int) ; 
 char* r_cmd_java_strtok (char const*,char,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int r_cmd_java_get_class_names_from_input (const char *input, char **class_name, ut32 *class_name_len, char **new_class_name, ut32 *new_class_name_len) {
	const char *p = input;

	ut32 cmd_sz = input && *input ? strlen (input) : 0;
	int res = false;

	if (!class_name || *class_name) {
		return res;
	} else if (!new_class_name || *new_class_name) {
		return res;
	} else if (!new_class_name_len || !class_name_len) {
		return res;
	}

	*new_class_name = NULL;
	*class_name_len = 0;

	if (p && *p && cmd_sz > 1) {
		const char *end;
		p = r_cmd_java_consumetok (p, ' ', cmd_sz);
		end = p && *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;

		if (p && end && p != end) {
			*class_name_len = end - p + 1;
			*class_name = malloc (*class_name_len);
			snprintf (*class_name, *class_name_len, "%s", p );
			cmd_sz = *class_name_len - 1 < cmd_sz ? cmd_sz - *class_name_len : 0;
		}

		if (*class_name && cmd_sz > 0) {
			p = r_cmd_java_consumetok (end+1, ' ', cmd_sz);
			end = p && *p ? r_cmd_java_strtok (p, ' ', -1) : NULL;

			if (!end && p && *p) {
				end = p + cmd_sz;
			}

			if (p && end && p != end) {
				*new_class_name_len = end - p + 1;
				*new_class_name = malloc (*new_class_name_len);
				snprintf (*new_class_name, *new_class_name_len, "%s", p );
				res = true;
			}
		}
	}
	return res;
}