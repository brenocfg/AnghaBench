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

/* Variables and functions */
 char*** fb_var_names ; 
 int num_atafb_predefined ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int get_video_mode(char *vname)
{
	char ***name_list;
	char **name;
	int i;

	name_list = fb_var_names;
	for (i = 0; i < num_atafb_predefined; i++) {
		name = *name_list++;
		if (!name || !*name)
			break;
		while (*name) {
			if (!strcmp(vname, *name))
				return i + 1;
			name++;
		}
	}
	return 0;
}