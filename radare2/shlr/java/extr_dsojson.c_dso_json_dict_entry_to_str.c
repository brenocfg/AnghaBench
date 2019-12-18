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
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DsoJsonDictEntry ;

/* Variables and functions */
 char* calloc (int,int) ; 
 char* dso_json_obj_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int strlen (char*) ; 

char * dso_json_dict_entry_to_str (DsoJsonDictEntry * entry) {
	char *res = NULL;
	if (entry) {
		char *key = dso_json_obj_to_str (entry->key);
		char *value = dso_json_obj_to_str (entry->value);
		if (key) {
			int len = 2 + 3 + strlen (key);
			if (value) len += strlen (value);
			res = calloc (len, 1);
			if (res) {
				if (value) {
					snprintf (res, len, "%s:%s", key, value);
				} else {
					snprintf (res, len, "%s:\"\"", key);
				}
			}
			free (key);
		}
		free (value);
	}
	return res;
}