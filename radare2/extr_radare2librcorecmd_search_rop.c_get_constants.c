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
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList* get_constants(const char *str) {
	RList *list;
	char *p, *data;
	if (!str) {
		return NULL;
	}

	data = strdup (str);
	list = r_list_newf (free);
	p = strtok (data, ",");
	while (p) {
		if (strtol (p, NULL, 0)) {
			r_list_append (list, (void*)strdup (p));
		}
		p = strtok (NULL, ",");
	}
	free (data);
	return list;
}