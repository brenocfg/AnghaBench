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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_arg (char const*,int,char*) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int get_arguments (char**arg, char const*arguments) {
	size_t arglen = strlen (arguments) + 1;
	char*tmp = malloc (arglen);
	if (!get_arg (arguments, 1, tmp)) {
		free (tmp); tmp = 0;
		return 0;
	} else {
		arg[0] = realloc (tmp, strlen (tmp) + 1); tmp = 0;
		tmp = malloc (arglen);
		if (!get_arg (arguments, 2, tmp)) {
			free (tmp); tmp = 0;
			return 1;
		} else {
			arg[1] = realloc (tmp, strlen (tmp) + 1); tmp = 0;
			tmp = malloc (arglen + 1);
			if (!get_arg (arguments, 3, tmp)) {
				free (tmp); tmp = 0;
				return 2;
			} else {
				arg[2] = realloc (tmp, strlen (tmp) + 1); tmp = 0;
				tmp = malloc (arglen + 1);
				if (get_arg (arguments, 4, tmp)) {
					free (tmp); tmp = 0;
					free (arg[0]); arg[0] = 0;
					free (arg[1]); arg[1] = 0;
					free (arg[2]); arg[2] = 0;
					return 4;
				}
				free (tmp); tmp = 0;
				return 3;
			}
		}
	}
}