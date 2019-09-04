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
 int /*<<< orphan*/  r_cons_print (char*) ; 
 char* r_syscmd_mkdir (char const*) ; 

__attribute__((used)) static int cmd_mkdir(void *data, const char *input) {
	char *res = r_syscmd_mkdir (input);
	if (res) {
		r_cons_print (res);
		free (res);
	}
	return 0;
}