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
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/  (*) (char*)) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static RList* parse_list (const char *str) {
	RList *list;
	char *line, *data, *p, *str_n;

	if (!str) {
		return NULL;
	}

	str_n = strdup (str);
	list = r_list_newf (free);
	if (!list) {
		free (str_n);
		return NULL;
	}
	line = strtok (str_n, "\n");
	data = strchr (line, '=');
	// TODO: use r_str_split()
	p = strtok (data + 1, ",");

	while (p) {
		r_list_append (list, (void*)strdup (p));
		p = strtok (NULL, ",");
	}

	free (str_n);
	return list;
}